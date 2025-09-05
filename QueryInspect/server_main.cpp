// server_main.cpp
#include <iostream>
#include <csignal>
#include <string>
#include "SQLSenseServer.h"

// Global server instance for signal handling
std::unique_ptr<SQLSenseServer> globalServer;

void signalHandler(int signal) {
    std::cout << "\n🛑 Received signal " << signal << ". Shutting down gracefully...\n";
    if (globalServer) {
        globalServer->stop();
    }
    exit(0);
}

void printWelcome() {
    std::cout << "\n";
    std::cout << "███████╗ ██████╗ ██╗     ███████╗███████╗███╗   ███╗███████╗███████╗\n";
    std::cout << "██╔════╝██╔═══██╗██║     ██╔════╝██╔════╝████╗ ████║██╔════╝██╔════╝\n";
    std::cout << "███████╗██║   ██║██║     ███████╗█████╗  ██╔████╔██║███████╗█████╗  \n";
    std::cout << "╚════██║██║▄▄ ██║██║     ╚════██║██╔══╝  ██║╚██╔╝██║╚════██║██╔══╝  \n";
    std::cout << "███████║╚██████╔╝███████╗███████║███████╗██║ ╚═╝ ██║███████║███████╗\n";
    std::cout << "╚══════╝ ╚══▀▀═╝ ╚══════╝╚══════╝╚══════╝╚═╝     ╚═╝╚══════╝╚══════╝\n";
    std::cout << "\n";
    std::cout << "🔍 Advanced SQL Query Analysis Server\n";
    std::cout << "======================================\n";
    std::cout << "Features:\n";
    std::cout << "  ✓ Real-time Syntax Analysis (Flex/Bison)\n";
    std::cout << "  ✓ Semantic Validation (Schema-aware)\n";
    std::cout << "  ✓ Type Compatibility Checking\n";
    std::cout << "  ✓ Table/Column Existence Validation\n";  
    std::cout << "  ✓ RESTful API for VS Code Integration\n";
    std::cout << "======================================\n\n";
}

void showUsage(const char* programName) {
    std::cout << "Usage: " << programName << " [OPTIONS]\n\n";
    std::cout << "Options:\n";
    std::cout << "  -p, --port PORT          Server port (default: 8080)\n";
    std::cout << "  -h, --host HOST          Server host (default: localhost)\n";
    std::cout << "  --mysql-host HOST        MySQL server host (default: localhost)\n";
    std::cout << "  --mysql-port PORT        MySQL server port (default: 3306)\n";
    std::cout << "  --mysql-user USER        MySQL username (default: root)\n";
    std::cout << "  --mysql-password PASS    MySQL password (default: empty)\n";
    std::cout << "  --help                   Show this help message\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << " -p 9000\n";
    std::cout << "  " << programName << " --mysql-user myuser --mysql-password mypass\n";
    std::cout << "  " << programName << " --host 0.0.0.0 -p 8080\n\n";
}

int main(int argc, char* argv[]) {
    printWelcome();
    
    // Parse command line arguments
    ServerConfig config; // Now this works!
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "--help") {
            showUsage(argv[0]);
            return 0;
        } else if ((arg == "-p" || arg == "--port") && i + 1 < argc) {
            config.port = std::stoi(argv[++i]);
        } else if ((arg == "-h" || arg == "--host") && i + 1 < argc) {
            config.host = argv[++i];
        } else if (arg == "--mysql-host" && i + 1 < argc) {
            config.mysql_host = argv[++i];
        } else if (arg == "--mysql-port" && i + 1 < argc) {
            config.mysql_port = std::stoi(argv[++i]);
        } else if (arg == "--mysql-user" && i + 1 < argc) {
            config.mysql_user = argv[++i];
        } else if (arg == "--mysql-password" && i + 1 < argc) {
            config.mysql_password = argv[++i];
        } else {
            std::cerr << "❌ Unknown argument: " << arg << "\n";
            showUsage(argv[0]);
            return 1;
        }
    }
    
    try {
        // Create and initialize server
        globalServer = std::make_unique<SQLSenseServer>(config);
        
        // Setup signal handlers for graceful shutdown
        std::signal(SIGINT, signalHandler);
        std::signal(SIGTERM, signalHandler);
        
        // Initialize the server
        if (!globalServer->initialize()) {
            std::cerr << "❌ Failed to initialize server\n";
            return 1;
        }
        
        // Start the server (this blocks)
        globalServer->run();
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Server error: " << e.what() << "\n";
        return 1;
    }
    
    std::cout << "👋 SQLSense server stopped. Goodbye!\n";
    return 0;
}
