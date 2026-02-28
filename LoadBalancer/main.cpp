/**
 * @file main.cpp
 * @brief Main entry point for Load Balancer simulation
 * @date February 2026
 * 
 * Loads configuration from file, initializes simulation components,
 * and runs the load balancer with dynamic server scaling.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "LoadBalancer.h"
#include "RequestGenerator.h"
#include "Logger.h"
#include "Colors.h"

/**
 * @brief Load simulation configuration from a file
 * @param filePath Path to the configuration file
 * @return SimulationConfig struct with loaded parameters
 */
SimulationConfig loadConfigFromFile(const std::string& filePath) {
    // Initialize with default values
    SimulationConfig config = {0};
    std::ifstream file(filePath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file: " << filePath << std::endl;
        exit(1);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Parse key=value pairs
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            // Trim whitespace
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            
            // Assign values to config
            if (key == "initialServers") config.initialServers = std::stoi(value);
            else if (key == "maxServers") config.maxServers = std::stoi(value);
            else if (key == "simulationLength") config.simulationLength = std::stoi(value);
            else if (key == "seed") config.seed = std::stoi(value);
            else if (key == "requestDelayMin") config.requestDelayMin = std::stoi(value);
            else if (key == "requestDelayMax") config.requestDelayMax = std::stoi(value);
            else if (key == "requestProcessingMin") config.requestProcessingMin = std::stoi(value);
            else if (key == "requestProcessingMax") config.requestProcessingMax = std::stoi(value);
            else if (key == "queueLowThreshold") config.queueLowThreshold = std::stoi(value);
            else if (key == "queueHighThreshold") config.queueHighThreshold = std::stoi(value);
            else if (key == "serverAdjustmentDelay") config.serverAdjustmentDelay = std::stoi(value);
            else if (key == "blockedIPs") config.blockedIPs = value;
        }
    }
    
    file.close();
    return config;
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    // Load configuration from file
    std::string configFilePath = argv[1];
    SimulationConfig config = loadConfigFromFile(configFilePath);
    
    // Create logger
    Logger logger("simulation.log", false); // Don't duplicate console output
    
    ConsoleColor::setColor(ConsoleColor::CYAN);
    std::cout << "========================================" << std::endl;
    std::cout << "Configuration loaded from: " << configFilePath << std::endl;
    std::cout << "========================================" << std::endl;
    ConsoleColor::reset();
    
    logger.log("Configuration loaded from: " + configFilePath);
    
    std::cout << "Simulation Parameters:" << std::endl;
    std::cout << "  Initial Servers: " << config.initialServers << std::endl;
    std::cout << "  Max Servers: " << config.maxServers << std::endl;
    std::cout << "  Simulation Length: " << config.simulationLength << " cycles" << std::endl;
    std::cout << std::endl;
    std::cout << "Request Generation:" << std::endl;
    std::cout << "  Seed: " << config.seed << std::endl;
    std::cout << "  Request Delay: " << config.requestDelayMin << "-" << config.requestDelayMax << " cycles" << std::endl;
    std::cout << "  Processing Time: " << config.requestProcessingMin << "-" << config.requestProcessingMax << " cycles" << std::endl;
    ConsoleColor::setColor(ConsoleColor::CYAN);
    std::cout << "========================================" << std::endl;
    ConsoleColor::reset();
    std::cout << std::endl;
    
    ConsoleColor::setColor(ConsoleColor::YELLOW);
    std::cout << "Starting simulation..." << std::endl;
    ConsoleColor::reset();

    // create load balancer with config and number of servers
    LoadBalancer lb = LoadBalancer(config, config.initialServers, &logger);

    // set up request generator
    RequestGenerator rg = RequestGenerator(config);

    // random number generator for request delays
    std::mt19937 rng(config.seed);
    std::uniform_int_distribution<int> delayDist(config.requestDelayMin, config.requestDelayMax);

    // generate a full request queue (about webservers * 100)
    std::cout << "Generating initial request queue (" << config.initialServers * 100 << " requests)..." << std::endl;
    for (int i = 0; i < config.initialServers * 100; i++) {
        lb.sendRequest(rg.generateRequest());
    }
    std::cout << "Initial queue generated. Queue size: " << lb.getQueueSize() << std::endl;
    std::cout << std::endl;
    
    // Log configuration and starting state
    logger.logConfiguration(config.initialServers, config.maxServers, config.simulationLength,
                           config.requestProcessingMin, config.requestProcessingMax, lb.getQueueSize());

    // start simulation and tick until simulation length is reached
    int elapsedTime = 0;
    int nextRequestTime = delayDist(rng); // schedule first new request

    ConsoleColor::setColor(ConsoleColor::YELLOW);
    std::cout << "Running simulation..." << std::endl;
    ConsoleColor::reset();
    std::cout << std::endl;

    while (elapsedTime < config.simulationLength) {
        lb.tick();

        // check if it is time to generate a new request
        if (elapsedTime >= nextRequestTime) {
            lb.sendRequest(rg.generateRequest());
            // schedule next request (random time between min and max delay)
            int randomDelay = delayDist(rng);
            nextRequestTime = elapsedTime + randomDelay;
        }

        // increment elapsed time
        elapsedTime++;
    }

    std::cout << std::endl;
    ConsoleColor::setColor(ConsoleColor::MAGENTA);
    std::cout << "Simulation complete!" << std::endl;
    ConsoleColor::reset();
    std::cout << "Final queue size: " << lb.getQueueSize() << std::endl;
    std::cout << "Final server count: " << lb.getServerCount() << std::endl;
    
    if (lb.getBlockedRequests() > 0) {
        ConsoleColor::setColor(ConsoleColor::RED);
        std::cout << "Firewall blocked requests: " << lb.getBlockedRequests() << std::endl;
        ConsoleColor::reset();
    }
    
    std::cout << std::endl;
    
    // Write summary to log
    logger.logSummary(config.simulationLength, lb.getServerCount(), lb.getQueueSize(), 
                      lb.getScalingEvents(), lb.getBlockedRequests());
    
    ConsoleColor::setColor(ConsoleColor::CYAN);
    std::cout << "Log file written to: simulation.log" << std::endl;
    ConsoleColor::reset();

    return 0;
}
