// src/extension.ts
import * as vscode from 'vscode';
import { SQLAnalyzer } from './sqlAnalyzer';

let analyzer: SQLAnalyzer;
let diagnosticCollection: vscode.DiagnosticCollection;
let statusBarItem: vscode.StatusBarItem;
let analysisTimer: NodeJS.Timeout | undefined;

export function activate(context: vscode.ExtensionContext) {
    console.log('🚀 SQLSense extension activated');
    
    // Initialize components
    analyzer = new SQLAnalyzer();
    diagnosticCollection = vscode.languages.createDiagnosticCollection('sqlsense');
    statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right, 100);
    
    // Register all disposables
    context.subscriptions.push(
        diagnosticCollection,
        statusBarItem,
        analyzer,
        
        // Document listeners
        vscode.workspace.onDidChangeTextDocument(onDocumentChange),
        vscode.workspace.onDidOpenTextDocument(onDocumentOpen),
        vscode.window.onDidChangeActiveTextEditor(onEditorChange),
        vscode.workspace.onDidCloseTextDocument(onDocumentClose),
        
        // Configuration listener
        vscode.workspace.onDidChangeConfiguration(onConfigurationChange),
        
        // Commands
        vscode.commands.registerCommand('sqlsense.analyzeQuery', commandAnalyzeQuery),
        vscode.commands.registerCommand('sqlsense.refreshSchema', commandRefreshSchema),
        vscode.commands.registerCommand('sqlsense.selectDatabase', commandSelectDatabase),
        vscode.commands.registerCommand('sqlsense.toggleAnalysis', commandToggleAnalysis),
        vscode.commands.registerCommand('sqlsense.serverStatus', commandServerStatus)
    );

    // Initial setup
    updateStatusBar();
    analyzeOpenSQLFiles();
    
    // Welcome message
    vscode.window.showInformationMessage(
        '🎉 SQLSense is now active! Start typing SQL to see real-time analysis.',
        'View Output', 'Settings'
    ).then(selection => {
        if (selection === 'View Output') {
            vscode.commands.executeCommand('workbench.action.output.toggleOutput');
        } else if (selection === 'Settings') {
            vscode.commands.executeCommand('workbench.action.openSettings', 'sqlsense');
        }
    });
}

function onDocumentChange(event: vscode.TextDocumentChangeEvent): void {
    if (event.document.languageId === 'sql' && event.contentChanges.length > 0) {
        const config = vscode.workspace.getConfiguration('sqlsense');
        if (config.get<boolean>('enableRealTimeAnalysis', true)) {
            debounceAnalysis(event.document);
        }
    }
}

function onDocumentOpen(document: vscode.TextDocument): void {
    if (document.languageId === 'sql') {
        analyzeDocument(document);
    }
}

function onEditorChange(editor: vscode.TextEditor | undefined): void {
    if (editor && editor.document.languageId === 'sql') {
        analyzeDocument(editor.document);
    }
}

function onDocumentClose(document: vscode.TextDocument): void {
    diagnosticCollection.delete(document.uri);
}

function onConfigurationChange(event: vscode.ConfigurationChangeEvent): void {
    if (event.affectsConfiguration('sqlsense')) {
        // Reload configuration
        analyzer = new SQLAnalyzer();
        updateStatusBar();
    }
}

function debounceAnalysis(document: vscode.TextDocument): void {
    if (analysisTimer) {
        clearTimeout(analysisTimer);
    }
    
    const config = vscode.workspace.getConfiguration('sqlsense');
    const delay = config.get<number>('analysisDelay', 1500);
    
    analysisTimer = setTimeout(() => {
        analyzeDocument(document);
    }, delay);
}

async function analyzeDocument(document: vscode.TextDocument): Promise<void> {
    if (document.languageId !== 'sql') {
        return;
    }

    const query = document.getText().trim();
    if (query.length === 0) {
        diagnosticCollection.delete(document.uri);
        return;
    }

    try {
        updateStatusBar('Analyzing...');
        
        const config = vscode.workspace.getConfiguration('sqlsense');
        const database = config.get<string>('defaultDatabase', '');
        
        const result = await analyzer.analyzeSQL(query, database || undefined);
        
        if (result) {
            const diagnostics = analyzer.convertToVSCodeDiagnostics(result, document);
            diagnosticCollection.set(document.uri, diagnostics);
            
            // Show success message for valid queries (optional)
            if (result.overall_valid && diagnostics.length === 0) {
                // Could show a subtle success indicator
            }
        }
        
        updateStatusBar();
        
    } catch (error) {
        console.error('Analysis failed:', error);
        updateStatusBar('Error');
        
        // Clear diagnostics on analysis failure
        diagnosticCollection.delete(document.uri);
    }
}

async function commandAnalyzeQuery(): Promise<void> {
    const editor = vscode.window.activeTextEditor;
    if (!editor || editor.document.languageId !== 'sql') {
        vscode.window.showWarningMessage('Please open an SQL file to analyze');
        return;
    }
    
    await analyzeDocument(editor.document);
    vscode.window.showInformationMessage('✅ SQL analysis completed');
}

async function commandRefreshSchema(): Promise<void> {
    const config = vscode.workspace.getConfiguration('sqlsense');
    const database = config.get<string>('defaultDatabase', '');
    
    await vscode.window.withProgress({
        location: vscode.ProgressLocation.Notification,
        title: "Refreshing database schema...",
        cancellable: false
    }, async () => {
        const success = await analyzer.refreshSchema(database || undefined);
        
        if (success) {
            vscode.window.showInformationMessage('🔄 Schema cache refreshed successfully');
            // Re-analyze open SQL files
            analyzeOpenSQLFiles();
        } else {
            vscode.window.showErrorMessage('❌ Failed to refresh schema cache');
        }
    });
}

async function commandSelectDatabase(): Promise<void> {
    try {
        const databases = await analyzer.getDatabases();
        
        if (databases.length === 0) {
            vscode.window.showWarningMessage('No databases found. Ensure the server is running and has database access.');
            return;
        }
        
        const selected = await vscode.window.showQuickPick(databases, {
            placeHolder: 'Select database for SQL analysis'
        });
        
        if (selected) {
            const config = vscode.workspace.getConfiguration('sqlsense');
            await config.update('defaultDatabase', selected, vscode.ConfigurationTarget.Workspace);
            
            vscode.window.showInformationMessage(`📊 Database changed to: ${selected}`);
            
            // Re-analyze current file
            const editor = vscode.window.activeTextEditor;
            if (editor && editor.document.languageId === 'sql') {
                analyzeDocument(editor.document);
            }
        }
    } catch (error) {
        vscode.window.showErrorMessage(`Failed to get databases: ${error}`);
    }
}

async function commandToggleAnalysis(): Promise<void> {
    const config = vscode.workspace.getConfiguration('sqlsense');
    const current = config.get<boolean>('enableRealTimeAnalysis', true);
    
    await config.update('enableRealTimeAnalysis', !current, vscode.ConfigurationTarget.Global);
    
    const status = !current ? 'enabled' : 'disabled';
    vscode.window.showInformationMessage(`⏯️ Real-time analysis ${status}`);
    updateStatusBar();
}

async function commandServerStatus(): Promise<void> {
    const isHealthy = await analyzer.checkServerHealth();
    const status = analyzer.getServerStatus();
    
    const message = `
Server Status: ${isHealthy ? '✅ Healthy' : '❌ Offline'}
Last Checked: ${status.lastChecked.toLocaleString()}
Semantic Analysis: ${status.semanticEnabled ? '✅ Enabled' : '❌ Disabled'}
${status.databaseCount ? `Databases: ${status.databaseCount}` : ''}
    `.trim();
    
    vscode.window.showInformationMessage(message, { modal: true }, 'Retry Connection').then(selection => {
        if (selection === 'Retry Connection') {
            analyzer.checkServerHealth();
        }
    });
}

function updateStatusBar(message?: string): void {
    const config = vscode.workspace.getConfiguration('sqlsense');
    const enabled = config.get<boolean>('enableRealTimeAnalysis', true);
    const status = analyzer.getServerStatus();
    
    if (message) {
        statusBarItem.text = `$(database) SQLSense: ${message}`;
    } else {
        const serverStatus = status.isHealthy ? '$(check)' : '$(error)';
        const analysisStatus = enabled ? 'On' : 'Off';
        statusBarItem.text = `$(database) SQLSense: ${serverStatus} ${analysisStatus}`;
    }
    
    statusBarItem.command = 'sqlsense.serverStatus';
    statusBarItem.tooltip = `SQLSense Server: ${status.isHealthy ? 'Connected' : 'Offline'}\nReal-time Analysis: ${enabled ? 'Enabled' : 'Disabled'}\nClick for details`;
    statusBarItem.show();
}

function analyzeOpenSQLFiles(): void {
    vscode.workspace.textDocuments
        .filter(doc => doc.languageId === 'sql')
        .forEach(doc => analyzeDocument(doc));
}

export function deactivate(): void {
    if (analysisTimer) {
        clearTimeout(analysisTimer);
    }
    
    if (diagnosticCollection) {
        diagnosticCollection.dispose();
    }
    
    if (statusBarItem) {
        statusBarItem.dispose();
    }
    
    console.log('👋 SQLSense extension deactivated');
}
