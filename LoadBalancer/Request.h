#ifndef REQUEST_H
#define REQUEST_H

#include <string>

// Enumeration for job types
enum class JobType {
    Processing,
    Streaming
};

// Configuration struct for simulation
struct SimulationConfig {
    int initialServers;       // Starting number of servers
    int maxServers;           // Maximum servers allowed
    int simulationLength;
    
    // Request generation settings
    int seed;
    int requestDelayMin;      // Min clock cycles between new requests
    int requestDelayMax;      // Max clock cycles between new requests
    int requestProcessingMin; // Min clock cycles to process a request
    int requestProcessingMax; // Max clock cycles to process a request
    
    // Server scaling settings
    int queueLowThreshold;    // Scale down if queue < this * numServers
    int queueHighThreshold;   // Scale up if queue > this * numServers
    int serverAdjustmentDelay; // Clock cycles to wait between server adjustments
    
    // Firewall settings (optional)
    std::string blockedIPs; // Comma-separated list of blocked IPs (empty = no blocking)
};

// Request struct
struct Request {
    std::string inIP;
    std::string outIP;
    int time;
    JobType jobType;
    
    Request(const std::string& inIP, const std::string& outIP, int time, JobType jobType);
};

#endif // REQUEST_H
