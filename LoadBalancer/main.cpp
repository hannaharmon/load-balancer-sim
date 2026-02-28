#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "LoadBalancer.h"
#include "RequestGenerator.h"

// Function to load configuration from file
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
    
    std::cout << "========================================" << std::endl;
    std::cout << "Configuration loaded from: " << configFilePath << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Simulation Parameters:" << std::endl;
    std::cout << "  Initial Servers: " << config.initialServers << std::endl;
    std::cout << "  Max Servers: " << config.maxServers << std::endl;
    std::cout << "  Simulation Length: " << config.simulationLength << " cycles" << std::endl;
    std::cout << std::endl;
    std::cout << "Request Generation:" << std::endl;
    std::cout << "  Seed: " << config.seed << std::endl;
    std::cout << "  Request Delay: " << config.requestDelayMin << "-" << config.requestDelayMax << " cycles" << std::endl;
    std::cout << "  Processing Time: " << config.requestProcessingMin << "-" << config.requestProcessingMax << " cycles" << std::endl;
    std::cout << std::endl;
    std::cout << "Server Scaling:" << std::endl;
    std::cout << "  Queue Low Threshold: " << config.queueLowThreshold << " * num_servers" << std::endl;
    std::cout << "  Queue High Threshold: " << config.queueHighThreshold << " * num_servers" << std::endl;
    std::cout << "  Adjustment Delay: " << config.serverAdjustmentDelay << " cycles" << std::endl;
    std::cout << std::endl;
    std::cout << "Firewall:" << std::endl;
    std::cout << "  Blocked IPs: " << (config.blockedIPs.empty() ? "(none)" : config.blockedIPs) << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Starting simulation..." << std::endl;

    // create load balancer with config and number of servers
    LoadBalancer lb = LoadBalancer(config, config.initialServers);

    // set up request generator
    RequestGenerator rg = RequestGenerator(config);

    // random number generator for request delays
    std::mt19937 rng(config.seed);
    std::uniform_int_distribution<int> delayDist(config.requestDelayMin, config.requestDelayMax);

    // generate a full request queue (initial webservers * 100)
    std::cout << "Generating initial request queue (" << config.initialServers * 100 << " requests)..." << std::endl;
    for (int i = 0; i < config.initialServers * 100; i++) {
        lb.sendRequest(rg.generateRequest());
    }
    std::cout << "Initial queue generated. Queue size: " << lb.getQueueSize() << std::endl;
    std::cout << std::endl;

    // start simulation and tick until simulation length is reached
    int elapsedTime = 0;
    int nextRequestTime = delayDist(rng); // schedule first new request

    std::cout << "Running simulation..." << std::endl;

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
    std::cout << "Simulation complete!" << std::endl;
    std::cout << "Final queue size: " << lb.getQueueSize() << std::endl;

    return 0;
}
