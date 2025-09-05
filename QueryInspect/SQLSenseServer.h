#pragma once
#include <httplib.h>
#include <json/json.h>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include "../include/QueryInspect.h"

// Move ServerConfig outside the class to fix aggregate initialization
struct ServerConfig {
    std::string host = "localhost";
    int port = 8080;
    std::string mysql_host = "localhost";
    int mysql_port = 3306;
    std::string mysql_user = "root";
    std::string mysql_password = "";
    bool enable_cors = true;
    int timeout_seconds = 30;
};

class SQLSenseServer {
private:
    std::unique_ptr<QueryInspect> inspector_;
    httplib::Server server_;
    int port_;
    bool isRunning_;
    std::mutex inspector_mutex_;
    ServerConfig config_;

public:
    // Now this works because ServerConfig is outside the class
    SQLSenseServer(const ServerConfig& config = ServerConfig{});
    ~SQLSenseServer();
    
    bool initialize();
    void run();
    void stop();
    
private:
    void setupRoutes();
    void setupCORS();
    void setupErrorHandlers();
    
    // Route handlers
    void handleHealthCheck(const httplib::Request& req, httplib::Response& res);
    void handleAnalyze(const httplib::Request& req, httplib::Response& res);
    void handleRefreshSchema(const httplib::Request& req, httplib::Response& res);
    void handleGetDatabases(const httplib::Request& req, httplib::Response& res);
    void handleSetDatabase(const httplib::Request& req, httplib::Response& res);
    
    // Utility methods
    void sendJsonResponse(httplib::Response& res, const Json::Value& json, int status = 200);
    void sendError(httplib::Response& res, int status, const std::string& message);
    Json::Value syntaxResultToJson(const SyntaxResult& result);
    Json::Value semanticResultToJson(const SemanticResult& result);
    Json::Value completeResultToJson(const CompleteAnalysisResult& result);
    
    void logRequest(const httplib::Request& req);
    void printServerInfo();
};
