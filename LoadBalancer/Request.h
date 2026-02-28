/**
 * @file Request.h
 * @brief Core data structures for the load balancer simulation
 * @date February 2026
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @enum JobType
 * @brief Enumeration for categorizing request types
 */
enum class JobType {
    Processing,  /**< CPU-intensive processing job */
    Streaming    /**< Data streaming job */
};

/**
 * @struct SimulationConfig
 * @brief Configuration parameters for the load balancer simulation
 * 
 * Contains all adjustable parameters loaded from configuration files.
 * Time values are measured in clock cycles (integer units).
 */
struct SimulationConfig {
    int initialServers;       /**< Starting number of web servers */
    int maxServers;           /**< Maximum capacity limit for servers */
    int simulationLength;     /**< Total clock cycles to simulate */
    
    int seed;                 /**< Random number generator seed for reproducibility */
    int requestDelayMin;      /**< Minimum clock cycles between new request arrivals */
    int requestDelayMax;      /**< Maximum clock cycles between new request arrivals */
    int requestProcessingMin; /**< Minimum clock cycles to process a request */
    int requestProcessingMax; /**< Maximum clock cycles to process a request */
    
    int queueLowThreshold;    /**< Scale down if queue < (this × numServers) */
    int queueHighThreshold;   /**< Scale up if queue > (this × numServers) */
    int serverAdjustmentDelay; /**< Clock cycles cooldown between scaling events */
    
    std::string blockedIPs;   /**< Comma-separated blocked IPs/CIDR ranges for firewall */
};

/**
 * @struct Request
 * @brief Represents a single client request to be processed
 */
struct Request {
    std::string inIP;    /**< Client IP address (dotted decimal notation) */
    std::string outIP;   /**< Server IP address responding to request */
    int time;            /**< Processing time required (clock cycles) */
    JobType jobType;     /**< Type of job (Processing or Streaming) */
    
    /**
     * @brief Constructor for Request
     * @param inIP Client IP address
     * @param outIP Server IP address
     * @param time Processing time in clock cycles
     * @param jobType Type of request job
     */
    Request(const std::string& inIP, const std::string& outIP, int time, JobType jobType);
};

#endif // REQUEST_H
