/**
 * @file RequestGenerator.h
 * @brief Random request generator for simulation
 * @date February 2026
 */

#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H

#include "Request.h"

/**
 * @class RequestGenerator
 * @brief Generates randomized client requests
 * 
 * Uses simulation configuration to create requests with random IPs,
 * processing times, and job types. Uses seeded RNG for reproducibility.
 */
class RequestGenerator {
private:
    SimulationConfig config;  /**< Configuration for request generation parameters */

public:
    /**
     * @brief Constructor for RequestGenerator
     * @param config Simulation configuration containing RNG seed and time ranges
     */
    RequestGenerator(const SimulationConfig& config);
    
    /**
     * @brief Generate a random request
     * @return Newly created request with random IP, processing time, and job type
     */
    Request generateRequest();
};

#endif // REQUESTGENERATOR_H
