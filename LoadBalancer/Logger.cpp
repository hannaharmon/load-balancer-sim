/**
 * @file Logger.cpp
 * @brief Implementation of Logger class
 * @date February 2026
 */

#include "Logger.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Logger(const std::string& filename, bool consoleOutput)
    : consoleOutput(consoleOutput) {
    logFile.open(filename);
    if (!logFile.is_open()) {
        std::cerr << "Warning: Could not open log file: " << filename << std::endl;
    }
    
    // Write header
    time_t now = time(0);
    char* dt = ctime(&now);
    log("========================================");
    log("Load Balancer Simulation Log");
    log("Started: " + std::string(dt));
    log("========================================");
}

Logger::~Logger() {
    close();
}

void Logger::log(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
    if (consoleOutput) {
        std::cout << message << std::endl;
    }
}

void Logger::logScalingUp(int cycle, int servers, int queueSize) {
    std::stringstream ss;
    ss << "[" << cycle << "] SCALING UP: Added server (now " << servers << " servers, queue: " << queueSize << ")";
    log(ss.str());
}

void Logger::logScalingDown(int cycle, int servers, int queueSize) {
    std::stringstream ss;
    ss << "[" << cycle << "] SCALING DOWN: Removed server (now " << servers << " servers, queue: " << queueSize << ")";
    log(ss.str());
}

void Logger::logConfiguration(int initialServers, int maxServers, int simulationLength, 
                               int processingMin, int processingMax, int startingQueueSize) {
    log("");
    log("========================================");
    log("SIMULATION CONFIGURATION");
    log("========================================");
    
    std::stringstream ss;
    ss << "Initial Servers: " << initialServers;
    log(ss.str());
    
    ss.str("");
    ss << "Max Servers: " << maxServers;
    log(ss.str());
    
    ss.str("");
    ss << "Simulation Length: " << simulationLength << " clock cycles";
    log(ss.str());
    
    ss.str("");
    ss << "Task Time Range: " << processingMin << "-" << processingMax << " cycles";
    log(ss.str());
    
    ss.str("");
    ss << "Starting Queue Size: " << startingQueueSize;
    log(ss.str());
    
    log("========================================");
    log("");
}

void Logger::logSummary(int totalCycles, int finalServers, int finalQueue, int scalingEvents, int blockedRequests) {
    log("");
    log("========================================");
    log("SIMULATION SUMMARY");
    log("========================================");
    
    std::stringstream ss;
    ss << "Total Cycles: " << totalCycles;
    log(ss.str());
    
    ss.str("");
    ss << "Ending Queue Size: " << finalQueue;
    log(ss.str());
    
    ss.str("");
    ss << "Final Server Count: " << finalServers;
    log(ss.str());
    
    ss.str("");
    ss << "Total Scaling Events: " << scalingEvents;
    log(ss.str());
    
    ss.str("");
    ss << "Blocked Requests (Firewall): " << blockedRequests;
    log(ss.str());
    
    ss.str("");
    ss << "Average Queue per Server: " << (finalServers > 0 ? finalQueue / finalServers : 0);
    log(ss.str());
    
    log("========================================");
}

void Logger::close() {
    if (logFile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now);
        log("Simulation ended: " + std::string(dt));
        logFile.close();
    }
}
