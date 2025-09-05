// src/sqlAnalyzer.ts
import axios, { AxiosError } from 'axios';
import * as vscode from 'vscode';
import { AnalysisResponse, ServerConfig, ServerStatus, SQLError } from './types';

export class SQLAnalyzer {
    private config: ServerConfig;
    private serverStatus: ServerStatus;
    private outputChannel: vscode.OutputChannel;

    constructor() {
        this.config = this.loadConfig();
        this.serverStatus = { isHealthy: false, lastChecked: new Date() };
        this.outputChannel = vscode.window.createOutputChannel('SQLSense');
        
        // Initial health check
        this.checkServerHealth();
    }

    private loadConfig(): ServerConfig {
        const config = vscode.workspace.getConfiguration('sqlsense');
        return {
            url: config.get<string>('serverUrl', 'http://localhost:8080'),
            timeout: 10000
        };
    }

    private log(level: 'info' | 'warn' | 'error', message: string): void {
        const timestamp = new Date().toISOString();
        const configLevel = vscode.workspace.getConfiguration('sqlsense').get<string>('logLevel', 'info');
        
        const levels = { debug: 0, info: 1, warn: 2, error: 3 };
        if (levels[level] >= levels[configLevel as keyof typeof levels]) {
            this.outputChannel.appendLine(`[${timestamp}] [${level.toUpperCase()}] ${message}`);
        }
    }

    async checkServerHealth(): Promise<boolean> {
        try {
            this.log('info', 'Checking server health...');
            const response = await axios.get(`${this.config.url}/health`, {
                timeout: 3000
            });
            
            this.serverStatus = {
                isHealthy: true,
                lastChecked: new Date(),
                semanticEnabled: response.data.semantic_enabled,
                databaseCount: response.data.database_count
            };
            
            this.log('info', `Server is healthy. Semantic analysis: ${response.data.semantic_enabled ? 'enabled' : 'disabled'}`);
            return true;
        } catch (error) {
            this.serverStatus = { isHealthy: false, lastChecked: new Date() };
            this.log('error', `Server health check failed: ${error}`);
            return false;
        }
    }

    async analyzeSQL(query: string, database?: string): Promise<AnalysisResponse | null> {
        if (!this.serverStatus.isHealthy) {
            const isHealthy = await this.checkServerHealth();
            if (!isHealthy) {
                throw new Error('SQLSense server is not responding');
            }
        }

        try {
            this.log('info', `Analyzing SQL query (${query.length} characters)`);
            
            const requestData: any = { query: query.trim() };
            if (database) {
                requestData.database = database;
            }

            const response = await axios.post<AnalysisResponse>(
                `${this.config.url}/analyze`,
                requestData,
                {
                    timeout: this.config.timeout,
                    headers: { 'Content-Type': 'application/json' }
                }
            );

            this.log('info', `Analysis completed. Valid: ${response.data.overall_valid}`);
            return response.data;
        } catch (error) {
            this.handleAnalysisError(error as AxiosError);
            return null;
        }
    }

    private handleAnalysisError(error: AxiosError): void {
        if (error.code === 'ECONNREFUSED') {
            this.serverStatus.isHealthy = false;
            this.log('error', 'Server connection refused');
            vscode.window.showErrorMessage(
                'SQLSense server is not running. Please start the server.',
                'Start Guide'
            ).then(selection => {
                if (selection === 'Start Guide') {
                    vscode.env.openExternal(vscode.Uri.parse('https://github.com/your-repo/sqlsense#server-setup'));
                }
            });
        } else if (error.response?.status === 400) {
            this.log('warn', 'Invalid request format');
        } else if (error.response?.status === 500) {
            this.log('error', 'Server internal error');
            vscode.window.showErrorMessage('SQLSense server encountered an internal error. Check server logs.');
        } else {
            this.log('error', `Analysis failed: ${error.message}`);
        }
    }

    convertToVSCodeDiagnostics(result: AnalysisResponse, document: vscode.TextDocument): vscode.Diagnostic[] {
        const diagnostics: vscode.Diagnostic[] = [];

        // Handle syntax errors
        if (result.syntax.status !== 'valid' && result.syntax.error_message) {
            const line = Math.max(0, (result.syntax.error_line || 1) - 1);
            const column = Math.max(0, (result.syntax.error_column || 1) - 1);
            
            let range: vscode.Range;
            try {
                const lineText = document.lineAt(line).text;
                const wordRange = document.getWordRangeAtPosition(new vscode.Position(line, column));
                range = wordRange || new vscode.Range(line, column, line, Math.min(column + 10, lineText.length));
            } catch {
                range = new vscode.Range(line, column, line, column + 5);
            }

            const diagnostic = new vscode.Diagnostic(
                range,
                `Syntax Error: ${result.syntax.error_message}`,
                vscode.DiagnosticSeverity.Error
            );
            diagnostic.source = 'SQLSense';
            diagnostic.code = 'syntax-error';
            diagnostics.push(diagnostic);
        }

        // Handle semantic errors
        if (result.semantic && !result.semantic.is_valid) {
            for (const issue of result.semantic.issues) {
                // For semantic errors, highlight the entire first line since we don't have precise locations
                const range = new vscode.Range(0, 0, 0, document.lineAt(0).text.length);
                
                const diagnostic = new vscode.Diagnostic(
                    range,
                    `Semantic Error: ${issue.message}`,
                    vscode.DiagnosticSeverity.Warning
                );
                diagnostic.source = 'SQLSense';
                diagnostic.code = 'semantic-error';
                
                // Add suggestion as related information
                if (issue.suggestion) {
                    diagnostic.relatedInformation = [
                        new vscode.DiagnosticRelatedInformation(
                            new vscode.Location(document.uri, range),
                            `💡 Suggestion: ${issue.suggestion}`
                        )
                    ];
                }
                
                diagnostics.push(diagnostic);
            }
        }

        // Handle semantic warnings
        if (result.semantic?.warnings) {
            for (const warning of result.semantic.warnings) {
                const range = new vscode.Range(0, 0, 0, document.lineAt(0).text.length);
                
                const diagnostic = new vscode.Diagnostic(
                    range,
                    `Warning: ${warning}`,
                    vscode.DiagnosticSeverity.Information
                );
                diagnostic.source = 'SQLSense';
                diagnostic.code = 'semantic-warning';
                diagnostics.push(diagnostic);
            }
        }

        return diagnostics;
    }

    async refreshSchema(database?: string): Promise<boolean> {
        try {
            const requestData = database ? { database } : {};
            await axios.post(`${this.config.url}/refresh-schema`, requestData, {
                timeout: 30000
            });
            this.log('info', `Schema refreshed for database: ${database || 'all'}`);
            return true;
        } catch (error) {
            this.log('error', `Schema refresh failed: ${error}`);
            return false;
        }
    }

    async getDatabases(): Promise<string[]> {
        try {
            const response = await axios.get<string[]>(`${this.config.url}/databases`, {
                timeout: 5000
            });
            return response.data;
        } catch (error) {
            this.log('error', `Failed to get databases: ${error}`);
            return [];
        }
    }

    getServerStatus(): ServerStatus {
        return this.serverStatus;
    }

    dispose(): void {
        this.outputChannel.dispose();
    }
}
