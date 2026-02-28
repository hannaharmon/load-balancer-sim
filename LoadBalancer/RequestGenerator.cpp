#include "RequestGenerator.h"
#include <random>
#include <sstream>

RequestGenerator::RequestGenerator(const SimulationConfig& config)
    : config(config) {
}

Request RequestGenerator::generateRequest() {
    // use config.seed-based RNG
    static std::mt19937 rng(config.seed);
    static std::uniform_int_distribution<int> ipOctet(0, 255);
    static std::uniform_int_distribution<int> processingTime(config.requestProcessingMin, config.requestProcessingMax);
    static std::uniform_int_distribution<int> jobTypeDist(0, 1);
    
    // generate random in/out IP addresses (format: xxx.xxx.xxx.xxx)
    std::stringstream inIP, outIP;
    inIP << ipOctet(rng) << "." << ipOctet(rng) << "." << ipOctet(rng) << "." << ipOctet(rng);
    outIP << ipOctet(rng) << "." << ipOctet(rng) << "." << ipOctet(rng) << "." << ipOctet(rng);
    
    // generate random processing time
    int time = processingTime(rng);
    
    // generate random job type (0 = processing, 1 = streaming)
    JobType jobType = (jobTypeDist(rng) == 0) ? JobType::Processing : JobType::Streaming;
    
    return Request(inIP.str(), outIP.str(), time, jobType);
}
