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
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.SQLAnalyzer = void 0;
// src/sqlAnalyzer.ts
const axios_1 = __importDefault(require("axios"));
const vscode = __importStar(require("vscode"));
class SQLAnalyzer {
    constructor() {
        this.config = this.loadConfig();
        this.serverStatus = { isHealthy: false, lastChecked: new Date() };
        this.outputChannel = vscode.window.createOutputChannel('SQLSense');
        // Initial health check
        this.checkServerHealth();
    }
    loadConfig() {
        const config = vscode.workspace.getConfiguration('sqlsense');
        return {
            url: config.get('serverUrl', 'http://localhost:8080'),
            timeout: 10000
        };
    }
    log(level, message) {
        const timestamp = new Date().toISOString();
        const configLevel = vscode.workspace.getConfiguration('sqlsense').get('logLevel', 'info');
        const levels = { debug: 0, info: 1, warn: 2, error: 3 };
        if (levels[level] >= levels[configLevel]) {
            this.outputChannel.appendLine(`[${timestamp}] [${level.toUpperCase()}] ${message}`);
        }
    }
    checkServerHealth() {
        return __awaiter(this, void 0, void 0, function* () {
            try {
                this.log('info', 'Checking server health...');
                const response = yield axios_1.default.get(`${this.config.url}/health`, {
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
            }
            catch (error) {
                this.serverStatus = { isHealthy: false, lastChecked: new Date() };
                this.log('error', `Server health check failed: ${error}`);
                return false;
            }
        });
    }
    analyzeSQL(query, database) {
        return __awaiter(this, void 0, void 0, function* () {
            if (!this.serverStatus.isHealthy) {
                const isHealthy = yield this.checkServerHealth();
                if (!isHealthy) {
                    throw new Error('SQLSense server is not responding');
                }
            }
            try {
                this.log('info', `Analyzing SQL query (${query.length} characters)`);
                const requestData = { query: query.trim() };
                if (database) {
                    requestData.database = database;
                }
                const response = yield axios_1.default.post(`${this.config.url}/analyze`, requestData, {
                    timeout: this.config.timeout,
                    headers: { 'Content-Type': 'application/json' }
                });
                this.log('info', `Analysis completed. Valid: ${response.data.overall_valid}`);
                return response.data;
            }
            catch (error) {
                this.handleAnalysisError(error);
                return null;
            }
        });
    }
    handleAnalysisError(error) {
        var _a, _b;
        if (error.code === 'ECONNREFUSED') {
            this.serverStatus.isHealthy = false;
            this.log('error', 'Server connection refused');
            vscode.window.showErrorMessage('SQLSense server is not running. Please start the server.', 'Start Guide').then(selection => {
                if (selection === 'Start Guide') {
                    vscode.env.openExternal(vscode.Uri.parse('https://github.com/your-repo/sqlsense#server-setup'));
                }
            });
        }
        else if (((_a = error.response) === null || _a === void 0 ? void 0 : _a.status) === 400) {
            this.log('warn', 'Invalid request format');
        }
        else if (((_b = error.response) === null || _b === void 0 ? void 0 : _b.status) === 500) {
            this.log('error', 'Server internal error');
            vscode.window.showErrorMessage('SQLSense server encountered an internal error. Check server logs.');
        }
        else {
            this.log('error', `Analysis failed: ${error.message}`);
        }
    }
    convertToVSCodeDiagnostics(result, document) {
        var _a;
        const diagnostics = [];
        // Handle syntax errors
        if (result.syntax.status !== 'valid' && result.syntax.error_message) {
            const line = Math.max(0, (result.syntax.error_line || 1) - 1);
            const column = Math.max(0, (result.syntax.error_column || 1) - 1);
            let range;
            try {
                const lineText = document.lineAt(line).text;
                const wordRange = document.getWordRangeAtPosition(new vscode.Position(line, column));
                range = wordRange || new vscode.Range(line, column, line, Math.min(column + 10, lineText.length));
            }
            catch (_b) {
                range = new vscode.Range(line, column, line, column + 5);
            }
            const diagnostic = new vscode.Diagnostic(range, `Syntax Error: ${result.syntax.error_message}`, vscode.DiagnosticSeverity.Error);
            diagnostic.source = 'SQLSense';
            diagnostic.code = 'syntax-error';
            diagnostics.push(diagnostic);
        }
        // Handle semantic errors
        if (result.semantic && !result.semantic.is_valid) {
            for (const issue of result.semantic.issues) {
                // For semantic errors, highlight the entire first line since we don't have precise locations
                const range = new vscode.Range(0, 0, 0, document.lineAt(0).text.length);
                const diagnostic = new vscode.Diagnostic(range, `Semantic Error: ${issue.message}`, vscode.DiagnosticSeverity.Warning);
                diagnostic.source = 'SQLSense';
                diagnostic.code = 'semantic-error';
                // Add suggestion as related information
                if (issue.suggestion) {
                    diagnostic.relatedInformation = [
                        new vscode.DiagnosticRelatedInformation(new vscode.Location(document.uri, range), `💡 Suggestion: ${issue.suggestion}`)
                    ];
                }
                diagnostics.push(diagnostic);
            }
        }
        // Handle semantic warnings
        if ((_a = result.semantic) === null || _a === void 0 ? void 0 : _a.warnings) {
            for (const warning of result.semantic.warnings) {
                const range = new vscode.Range(0, 0, 0, document.lineAt(0).text.length);
                const diagnostic = new vscode.Diagnostic(range, `Warning: ${warning}`, vscode.DiagnosticSeverity.Information);
                diagnostic.source = 'SQLSense';
                diagnostic.code = 'semantic-warning';
                diagnostics.push(diagnostic);
            }
        }
        return diagnostics;
    }
    refreshSchema(database) {
        return __awaiter(this, void 0, void 0, function* () {
            try {
                const requestData = database ? { database } : {};
                yield axios_1.default.post(`${this.config.url}/refresh-schema`, requestData, {
                    timeout: 30000
                });
                this.log('info', `Schema refreshed for database: ${database || 'all'}`);
                return true;
            }
            catch (error) {
                this.log('error', `Schema refresh failed: ${error}`);
                return false;
            }
        });
    }
    getDatabases() {
        return __awaiter(this, void 0, void 0, function* () {
            try {
                const response = yield axios_1.default.get(`${this.config.url}/databases`, {
                    timeout: 5000
                });
                return response.data;
            }
            catch (error) {
                this.log('error', `Failed to get databases: ${error}`);
                return [];
            }
        });
    }
    getServerStatus() {
        return this.serverStatus;
    }
    dispose() {
        this.outputChannel.dispose();
    }
}
exports.SQLAnalyzer = SQLAnalyzer;
