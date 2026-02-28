/**
 * @file Logger.h
 * @brief File and console logging system
 * @date February 2026
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>

/**
 * @class Logger
 * @brief Handles logging of simulation events to file and console
 * 
 * Logs scaling events, simulation parameters, and generates a final
 * summary with timestamps. Outputs to both simulation.log and console.
 */
class Logger {
private:
    std::ofstream logFile;  /**< Output file stream */
    bool consoleOutput;     /**< Whether to echo to console */
    
public:
    /**
     * @brief Constructor for Logger
     * @param filename Log file path
     * @param consoleOutput Whether to also print to console (default: true)
     */
    Logger(const std::string& filename, bool consoleOutput = true);
    
    /**
     * @brief Destructor - ensures file is closed
     */
    ~Logger();
    
    /**
     * @brief Log a generic message
     * @param message Text to log
     */
    void log(const std::string& message);
    
    /**
     * @brief Log a scaling up event
     * @param cycle Current clock cycle
     * @param servers New server count
     * @param queueSize Current queue size
     */
    void logScalingUp(int cycle, int servers, int queueSize);
    
    /**
     * @brief Log a scaling down event
     * @param cycle Current clock cycle
     * @param servers New server count
     * @param queueSize Current queue size
     */
    void logScalingDown(int cycle, int servers, int queueSize);
    
    /**
     * @brief Log simulation configuration and initial state
     * @param initialServers Starting number of servers
     * @param maxServers Maximum server capacity
     * @param simulationLength Total cycles to simulate
     * @param processingMin Minimum processing time (cycles)
     * @param processingMax Maximum processing time (cycles)
     * @param startingQueueSize Initial queue size
     */
    void logConfiguration(int initialServers, int maxServers, int simulationLength, 
                          int processingMin, int processingMax, int startingQueueSize);
    
    /**
     * @brief Log final simulation summary
     * @param totalCycles Total simulation length
     * @param finalServers Final server count
     * @param finalQueue Final queue size
     * @param scalingEvents Total scaling operations
     * @param blockedRequests Firewall-blocked request count (default: 0)
     */
    void logSummary(int totalCycles, int finalServers, int finalQueue, int scalingEvents, int blockedRequests = 0);
    
    /**
     * @brief Explicitly close the log file
     */
    void close();
};

#endif // LOGGER_H
