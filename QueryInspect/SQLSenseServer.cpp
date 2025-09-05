#include "SQLSenseServer.h"

SQLSenseServer::SQLSenseServer(const ServerConfig& config) 
    : config_(config), port_(config.port), isRunning_(false) {
    inspector_ = std::make_unique<QueryInspect>();
}

SQLSenseServer::~SQLSenseServer() {
    stop();
}

bool SQLSenseServer::initialize() {
    std::cout << "🔧 Initializing SQLSense Server...\n";
    
    // Initialize semantic analysis with your existing method
    bool semanticEnabled = inspector_->initializeSemanticAnalysis(
        config_.mysql_host, 
        config_.mysql_port,
        config_.mysql_user, 
        config_.mysql_password
    );
    
    if (semanticEnabled) {
        std::cout << "✅ Semantic analysis initialized!\n";
        
        // Show available databases
        auto databases = inspector_->getAvailableDatabases();
        if (!databases.empty()) {
            std::cout << "📂 Available databases: ";
            for (size_t i = 0; i < databases.size(); ++i) {
                std::cout << databases[i];
                if (i < databases.size() - 1) std::cout << ", ";
            }
            std::cout << "\n";
            
            // Set first database as default
            inspector_->setDefaultDatabase(databases[0]);
            std::cout << "🎯 Default database: " << databases[0] << "\n";
        }
    } else {
        std::cout << "⚠️  Semantic analysis unavailable (syntax-only mode)\n";
    }
    
    // Setup server routes and middleware
    setupCORS();
    setupRoutes();
    setupErrorHandlers();
    
    std::cout << "✅ Server initialization complete!\n";
    return true;
}

void SQLSenseServer::setupCORS() {
    if (!config_.enable_cors) return;
    
    server_.set_pre_routing_handler([](const httplib::Request& req, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS, PUT, DELETE");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
        res.set_header("Access-Control-Max-Age", "3600");
        
        if (req.method == "OPTIONS") {
            res.status = 200;
            return httplib::Server::HandlerResponse::Handled;
        }
        
        return httplib::Server::HandlerResponse::Unhandled;
    });
}

void SQLSenseServer::setupRoutes() {
    // Health check endpoint
    server_.Get("/health", [this](const httplib::Request& req, httplib::Response& res) {
        handleHealthCheck(req, res);
    });
    
    // Main analysis endpoint
    server_.Post("/analyze", [this](const httplib::Request& req, httplib::Response& res) {
        logRequest(req);
        handleAnalyze(req, res);
    });
    
    // Schema management endpoints
    server_.Post("/refresh-schema", [this](const httplib::Request& req, httplib::Response& res) {
        logRequest(req);
        handleRefreshSchema(req, res);
    });
    
    server_.Get("/databases", [this](const httplib::Request& req, httplib::Response& res) {
        handleGetDatabases(req, res);
    });
    
    server_.Post("/set-database", [this](const httplib::Request& req, httplib::Response& res) {
        logRequest(req);
        handleSetDatabase(req, res);
    });
    
    // Server info endpoint
    server_.Get("/info", [this](const httplib::Request& req, httplib::Response& res) {
        Json::Value info;
        info["name"] = "SQLSense Server";
        info["version"] = "1.0.0";
        info["semantic_enabled"] = inspector_->isSemanticAnalysisEnabled();
        info["uptime"] = std::time(nullptr); // You can track actual uptime
        
        sendJsonResponse(res, info);
    });
}

void SQLSenseServer::setupErrorHandlers() {
    server_.set_error_handler([](const httplib::Request& req, httplib::Response& res) {
        Json::Value error;
        error["error"] = "Internal server error";
        error["status"] = res.status;
        error["path"] = req.path;
        
        Json::StreamWriterBuilder builder;
        res.set_content(Json::writeString(builder, error), "application/json");
    });
}

void SQLSenseServer::handleHealthCheck(const httplib::Request& req, httplib::Response& res) {
    Json::Value response;
    response["status"] = "healthy";
    response["timestamp"] = std::time(nullptr);
    response["semantic_enabled"] = inspector_->isSemanticAnalysisEnabled();
    response["server"] = "SQLSense v1.0.0";
    
    if (inspector_->isSemanticAnalysisEnabled()) {
        auto databases = inspector_->getAvailableDatabases();
        response["database_count"] = static_cast<int>(databases.size());
    }
    
    sendJsonResponse(res, response);
}

void SQLSenseServer::handleAnalyze(const httplib::Request& req, httplib::Response& res) {
    try {
        Json::Value requestJson;
        Json::Reader reader;
        
        if (!reader.parse(req.body, requestJson)) {
            sendError(res, 400, "Invalid JSON format");
            return;
        }
        
        if (!requestJson.isMember("query") || !requestJson["query"].isString()) {
            sendError(res, 400, "Missing or invalid 'query' field");
            return;
        }
        
        std::string sqlQuery = requestJson["query"].asString();
        
        // Handle database parameter
        if (requestJson.isMember("database") && requestJson["database"].isString()) {
            std::string database = requestJson["database"].asString();
            if (!database.empty()) {
                std::lock_guard<std::mutex> lock(inspector_mutex_);
                inspector_->setDefaultDatabase(database);
                std::cout << "🎯 Set database to: " << database << " for this request\n";
            }
        }
        
        std::cout << "🔍 Analyzing query: " << sqlQuery.substr(0, 50) << "...\n";
        
        // Perform analysis using your existing method
        CompleteAnalysisResult result;
        {
            std::lock_guard<std::mutex> lock(inspector_mutex_);
            result = inspector_->analyzeComplete(sqlQuery);
        }
        
        // Convert result to JSON
        Json::Value response = completeResultToJson(result);
        
        sendJsonResponse(res, response);
        
        std::cout << "✅ Analysis completed for query\n";
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Analysis error: " << e.what() << "\n";
        sendError(res, 500, "Analysis failed: " + std::string(e.what()));
    }
}

void SQLSenseServer::handleRefreshSchema(const httplib::Request& req, httplib::Response& res) {
    try {
        if (!inspector_->isSemanticAnalysisEnabled()) {
            sendError(res, 503, "Semantic analysis is not enabled");
            return;
        }
        
        std::cout << "🔄 Refreshing schema cache...\n";
        
        {
            std::lock_guard<std::mutex> lock(inspector_mutex_);
            inspector_->refreshSchemaCache();
        }
        
        Json::Value response;
        response["success"] = true;
        response["message"] = "Schema cache refreshed successfully";
        response["timestamp"] = std::time(nullptr);
        
        sendJsonResponse(res, response);
        
        std::cout << "✅ Schema cache refreshed!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Schema refresh error: " << e.what() << "\n";
        sendError(res, 500, "Schema refresh failed: " + std::string(e.what()));
    }
}

void SQLSenseServer::handleGetDatabases(const httplib::Request& req, httplib::Response& res) {
    try {
        if (!inspector_->isSemanticAnalysisEnabled()) {
            sendError(res, 503, "Semantic analysis is not enabled");
            return;
        }
        
        std::vector<std::string> databases;
        {
            std::lock_guard<std::mutex> lock(inspector_mutex_);
            databases = inspector_->getAvailableDatabases();
        }
        
        Json::Value response(Json::arrayValue);
        for (const auto& db : databases) {
            response.append(db);
        }
        
        sendJsonResponse(res, response);
        
    } catch (const std::exception& e) {
        sendError(res, 500, "Failed to get databases: " + std::string(e.what()));
    }
}

void SQLSenseServer::handleSetDatabase(const httplib::Request& req, httplib::Response& res) {
    try {
        Json::Value requestJson;
        Json::Reader reader;
        
        if (!reader.parse(req.body, requestJson)) {
            sendError(res, 400, "Invalid JSON format");
            return;
        }
        
        if (!requestJson.isMember("database") || !requestJson["database"].isString()) {
            sendError(res, 400, "Missing or invalid 'database' field");
            return;
        }
        
        std::string database = requestJson["database"].asString();
        
        {
            std::lock_guard<std::mutex> lock(inspector_mutex_);
            inspector_->setDefaultDatabase(database);
        }
        
        Json::Value response;
        response["success"] = true;
        response["database"] = database;
        response["message"] = "Default database set successfully";
        
        sendJsonResponse(res, response);
        
        std::cout << "🎯 Default database set to: " << database << "\n";
        
    } catch (const std::exception& e) {
        sendError(res, 500, "Failed to set database: " + std::string(e.what()));
    }
}

Json::Value SQLSenseServer::syntaxResultToJson(const SyntaxResult& result) {
    Json::Value json;
    
    json["status"] = (result.status == SyntaxStatus::VALID) ? "valid" : 
                    (result.status == SyntaxStatus::INCOMPLETE) ? "incomplete" : "invalid";
    
    if (result.status != SyntaxStatus::VALID) {
        json["error_message"] = result.errorMessage;
        json["error_line"] = result.errorLine;
        json["error_column"] = result.errorColumn;
    }
    
    // Add components if available
    // You might need to extend this based on your QueryComponents structure
    
    return json;
}

Json::Value SQLSenseServer::semanticResultToJson(const SemanticResult& result) {
    Json::Value json;
    
    json["is_valid"] = result.isValid;
    
    // Issues/Errors
    json["issues"] = Json::Value(Json::arrayValue);
    for (const auto& issue : result.issues) {
        Json::Value issueJson;
        issueJson["message"] = issue.message;
        if (!issue.suggestion.empty()) {
            issueJson["suggestion"] = issue.suggestion;
        }
        // Add other issue fields based on your SemanticIssue structure
        json["issues"].append(issueJson);
    }
    
    // Warnings
    json["warnings"] = Json::Value(Json::arrayValue);
    for (const auto& warning : result.warnings) {
        json["warnings"].append(warning);
    }
    
    return json;
}

Json::Value SQLSenseServer::completeResultToJson(const CompleteAnalysisResult& result) {
    Json::Value json;
    
    json["overall_valid"] = result.overallValid;
    json["syntax"] = syntaxResultToJson(result.syntaxResult);
    
    if (inspector_->isSemanticAnalysisEnabled()) {
        json["semantic"] = semanticResultToJson(result.semanticResult);
    } else {
        json["semantic"] = Json::Value(Json::nullValue);
    }
    
    return json;
}

void SQLSenseServer::sendJsonResponse(httplib::Response& res, const Json::Value& json, int status) {
    res.status = status;
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";  // Compact JSON
    res.set_content(Json::writeString(builder, json), "application/json");
}

void SQLSenseServer::sendError(httplib::Response& res, int status, const std::string& message) {
    Json::Value error;
    error["error"] = message;
    error["status"] = status;
    error["timestamp"] = std::time(nullptr);
    
    sendJsonResponse(res, error, status);
}

void SQLSenseServer::logRequest(const httplib::Request& req) {
    std::cout << "📡 " << req.method << " " << req.path;
    if (!req.body.empty()) {
        std::cout << " (body: " << req.body.length() << " bytes)";
    }
    std::cout << "\n";
}

void SQLSenseServer::printServerInfo() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "🚀 SQLSense Server is running!\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "🌐 Server URL: http://" << config_.host << ":" << port_ << "\n";
    std::cout << "📊 Health Check: http://" << config_.host << ":" << port_ << "/health\n";
    std::cout << "🔍 Analysis Endpoint: POST http://" << config_.host << ":" << port_ << "/analyze\n";
    std::cout << "📂 Databases: GET http://" << config_.host << ":" << port_ << "/databases\n";
    std::cout << "🧠 Semantic Analysis: " << (inspector_->isSemanticAnalysisEnabled() ? "✅ Enabled" : "❌ Disabled") << "\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "Press Ctrl+C to stop the server\n\n";
}

void SQLSenseServer::run() {
    if (isRunning_) {
        std::cout << "⚠️  Server is already running!\n";
        return;
    }
    
    printServerInfo();
    isRunning_ = true;
    
    // Set server timeout
    server_.set_read_timeout(config_.timeout_seconds);
    server_.set_write_timeout(config_.timeout_seconds);
    
    if (!server_.listen(config_.host, port_)) {
        std::cerr << "❌ Failed to start server on " << config_.host << ":" << port_ << "\n";
        isRunning_ = false;
        return;
    }
    
    isRunning_ = false;
}

void SQLSenseServer::stop() {
    if (isRunning_) {
        std::cout << "🛑 Stopping SQLSense server...\n";
        server_.stop();
        isRunning_ = false;
    }
}
