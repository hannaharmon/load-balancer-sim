#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H

#include "Request.h"

class RequestGenerator {
private:
    SimulationConfig config;

public:
    RequestGenerator(const SimulationConfig& config);
    Request generateRequest();
};

#endif // REQUESTGENERATOR_H
