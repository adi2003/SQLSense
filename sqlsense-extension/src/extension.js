"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.deactivate = exports.activate = void 0;
// src/extension.ts
const vscode = __importStar(require("vscode"));
const sqlAnalyzer_1 = require("./sqlAnalyzer");
let analyzer;
let diagnosticCollection;
let statusBarItem;
let analysisTimer;
function activate(context) {
    console.log('🚀 SQLSense extension activated');
    // Initialize components
    analyzer = new sqlAnalyzer_1.SQLAnalyzer();
    diagnosticCollection = vscode.languages.createDiagnosticCollection('sqlsense');
    statusBarItem = vscode.window.createStatusBarItem(vscode.StatusBarAlignment.Right, 100);
    // Register all disposables
    context.subscriptions.push(diagnosticCollection, statusBarItem, analyzer, 
    // Document listeners
    vscode.workspace.onDidChangeTextDocument(onDocumentChange), vscode.workspace.onDidOpenTextDocument(onDocumentOpen), vscode.window.onDidChangeActiveTextEditor(onEditorChange), vscode.workspace.onDidCloseTextDocument(onDocumentClose), 
    // Configuration listener
    vscode.workspace.onDidChangeConfiguration(onConfigurationChange), 
    // Commands
    vscode.commands.registerCommand('sqlsense.analyzeQuery', commandAnalyzeQuery), vscode.commands.registerCommand('sqlsense.refreshSchema', commandRefreshSchema), vscode.commands.registerCommand('sqlsense.selectDatabase', commandSelectDatabase), vscode.commands.registerCommand('sqlsense.toggleAnalysis', commandToggleAnalysis), vscode.commands.registerCommand('sqlsense.serverStatus', commandServerStatus));
    // Initial setup
    updateStatusBar();
    analyzeOpenSQLFiles();
    // Welcome message
    vscode.window.showInformationMessage('🎉 SQLSense is now active! Start typing SQL to see real-time analysis.', 'View Output', 'Settings').then(selection => {
        if (selection === 'View Output') {
            vscode.commands.executeCommand('workbench.action.output.toggleOutput');
        }
        else if (selection === 'Settings') {
            vscode.commands.executeCommand('workbench.action.openSettings', 'sqlsense');
        }
    });
}
exports.activate = activate;
function onDocumentChange(event) {
    if (event.document.languageId === 'sql' && event.contentChanges.length > 0) {
        const config = vscode.workspace.getConfiguration('sqlsense');
        if (config.get('enableRealTimeAnalysis', true)) {
            debounceAnalysis(event.document);
        }
    }
}
function onDocumentOpen(document) {
    if (document.languageId === 'sql') {
        analyzeDocument(document);
    }
}
function onEditorChange(editor) {
    if (editor && editor.document.languageId === 'sql') {
        analyzeDocument(editor.document);
    }
}
function onDocumentClose(document) {
    diagnosticCollection.delete(document.uri);
}
function onConfigurationChange(event) {
    if (event.affectsConfiguration('sqlsense')) {
        // Reload configuration
        analyzer = new sqlAnalyzer_1.SQLAnalyzer();
        updateStatusBar();
    }
}
function debounceAnalysis(document) {
    if (analysisTimer) {
        clearTimeout(analysisTimer);
    }
    const config = vscode.workspace.getConfiguration('sqlsense');
    const delay = config.get('analysisDelay', 1500);
    analysisTimer = setTimeout(() => {
        analyzeDocument(document);
    }, delay);
}
function analyzeDocument(document) {
    return __awaiter(this, void 0, void 0, function* () {
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
            const database = config.get('defaultDatabase', '');
            const result = yield analyzer.analyzeSQL(query, database || undefined);
            if (result) {
                const diagnostics = analyzer.convertToVSCodeDiagnostics(result, document);
                diagnosticCollection.set(document.uri, diagnostics);
                // Show success message for valid queries (optional)
                if (result.overall_valid && diagnostics.length === 0) {
                    // Could show a subtle success indicator
                }
            }
            updateStatusBar();
        }
        catch (error) {
            console.error('Analysis failed:', error);
            updateStatusBar('Error');
            // Clear diagnostics on analysis failure
            diagnosticCollection.delete(document.uri);
        }
    });
}
function commandAnalyzeQuery() {
    return __awaiter(this, void 0, void 0, function* () {
        const editor = vscode.window.activeTextEditor;
        if (!editor || editor.document.languageId !== 'sql') {
            vscode.window.showWarningMessage('Please open an SQL file to analyze');
            return;
        }
        yield analyzeDocument(editor.document);
        vscode.window.showInformationMessage('✅ SQL analysis completed');
    });
}
function commandRefreshSchema() {
    return __awaiter(this, void 0, void 0, function* () {
        const config = vscode.workspace.getConfiguration('sqlsense');
        const database = config.get('defaultDatabase', '');
        yield vscode.window.withProgress({
            location: vscode.ProgressLocation.Notification,
            title: "Refreshing database schema...",
            cancellable: false
        }, () => __awaiter(this, void 0, void 0, function* () {
            const success = yield analyzer.refreshSchema(database || undefined);
            if (success) {
                vscode.window.showInformationMessage('🔄 Schema cache refreshed successfully');
                // Re-analyze open SQL files
                analyzeOpenSQLFiles();
            }
            else {
                vscode.window.showErrorMessage('❌ Failed to refresh schema cache');
            }
        }));
    });
}
function commandSelectDatabase() {
    return __awaiter(this, void 0, void 0, function* () {
        try {
            const databases = yield analyzer.getDatabases();
            if (databases.length === 0) {
                vscode.window.showWarningMessage('No databases found. Ensure the server is running and has database access.');
                return;
            }
            const selected = yield vscode.window.showQuickPick(databases, {
                placeHolder: 'Select database for SQL analysis'
            });
            if (selected) {
                const config = vscode.workspace.getConfiguration('sqlsense');
                yield config.update('defaultDatabase', selected, vscode.ConfigurationTarget.Workspace);
                vscode.window.showInformationMessage(`📊 Database changed to: ${selected}`);
                // Re-analyze current file
                const editor = vscode.window.activeTextEditor;
                if (editor && editor.document.languageId === 'sql') {
                    analyzeDocument(editor.document);
                }
            }
        }
        catch (error) {
            vscode.window.showErrorMessage(`Failed to get databases: ${error}`);
        }
    });
}
function commandToggleAnalysis() {
    return __awaiter(this, void 0, void 0, function* () {
        const config = vscode.workspace.getConfiguration('sqlsense');
        const current = config.get('enableRealTimeAnalysis', true);
        yield config.update('enableRealTimeAnalysis', !current, vscode.ConfigurationTarget.Global);
        const status = !current ? 'enabled' : 'disabled';
        vscode.window.showInformationMessage(`⏯️ Real-time analysis ${status}`);
        updateStatusBar();
    });
}
function commandServerStatus() {
    return __awaiter(this, void 0, void 0, function* () {
        const isHealthy = yield analyzer.checkServerHealth();
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
    });
}
function updateStatusBar(message) {
    const config = vscode.workspace.getConfiguration('sqlsense');
    const enabled = config.get('enableRealTimeAnalysis', true);
    const status = analyzer.getServerStatus();
    if (message) {
        statusBarItem.text = `$(database) SQLSense: ${message}`;
    }
    else {
        const serverStatus = status.isHealthy ? '$(check)' : '$(error)';
        const analysisStatus = enabled ? 'On' : 'Off';
        statusBarItem.text = `$(database) SQLSense: ${serverStatus} ${analysisStatus}`;
    }
    statusBarItem.command = 'sqlsense.serverStatus';
    statusBarItem.tooltip = `SQLSense Server: ${status.isHealthy ? 'Connected' : 'Offline'}\nReal-time Analysis: ${enabled ? 'Enabled' : 'Disabled'}\nClick for details`;
    statusBarItem.show();
}
function analyzeOpenSQLFiles() {
    vscode.workspace.textDocuments
        .filter(doc => doc.languageId === 'sql')
        .forEach(doc => analyzeDocument(doc));
}
function deactivate() {
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
exports.deactivate = deactivate;
