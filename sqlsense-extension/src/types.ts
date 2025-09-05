// src/types.ts
export interface ServerConfig {
  url: string;
  timeout: number;
}

export interface SQLError {
  type: 'syntax' | 'semantic';
  message: string;
  line: number;
  column: number;
  severity: 'error' | 'warning' | 'info';
  suggestion?: string;
}

export interface AnalysisResponse {
  overall_valid: boolean;
  syntax: {
    status: 'valid' | 'invalid' | 'incomplete';
    error_message?: string;
    error_line?: number;
    error_column?: number;
  };
  semantic?: {
    is_valid: boolean;
    issues: Array<{
      message: string;
      suggestion?: string;
    }>;
    warnings: string[];
  } | null;
}

export interface ServerStatus {
  isHealthy: boolean;
  lastChecked: Date;
  semanticEnabled?: boolean;
  databaseCount?: number;
}
