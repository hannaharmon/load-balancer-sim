#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include "Request.h"
#include "Webserver.h"
#include "Firewall.h"

class LoadBalancer {
private:
    std::queue<Request> requestQueue;
    std::vector<Webserver> servers;
    SimulationConfig config;
    Firewall firewall;
    int elapsedTime;
    int lastServerAdjustment;

public:
    LoadBalancer(const SimulationConfig& config, int numServers);
    int getQueueSize();
    void sendRequest(const Request& r);
    void tick();
    Request getNextRequest();
    void addServer();
    void removeServer();
};

#endif // LOADBALANCER_H
