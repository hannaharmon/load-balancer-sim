#include "LoadBalancer.h"
#include <unordered_set>
#include <iostream>
#include <sstream>

LoadBalancer::LoadBalancer(const SimulationConfig& config, int numServers)
    : config(config), firewall(std::unordered_set<std::string>()), elapsedTime(0), lastServerAdjustment(0) {
    // parse blocked IPs from config
    if (!config.blockedIPs.empty()) {
        std::unordered_set<std::string> blockedIPSet;
        std::stringstream ss(config.blockedIPs);
        std::string ip;
        while (std::getline(ss, ip, ',')) {
            // trim whitespace
            ip.erase(0, ip.find_first_not_of(" \t"));
            ip.erase(ip.find_last_not_of(" \t") + 1);
            if (!ip.empty()) {
                blockedIPSet.insert(ip);
            }
        }
        firewall = Firewall(blockedIPSet);
    }
    
    // initialize servers
    for (int i = 0; i < numServers; i++) {
        servers.push_back(Webserver(i));
    }
}

int LoadBalancer::getQueueSize() {
    return requestQueue.size();
}

void LoadBalancer::sendRequest(const Request& r) {
    // check if IP is blocked by firewall
    if (!firewall.isBlocked(r.inIP)) {
        requestQueue.push(r);
    }
    // if blocked, silently drop the request
}

void LoadBalancer::tick() {
    // tick all servers to process their current requests
    for (auto& server : servers) {
        server.tick();
    }
    
    // assign requests from queue to idle servers
    for (auto& server : servers) {
        if (server.isIdle() && !requestQueue.empty()) {
            Request r = requestQueue.front();
            requestQueue.pop();
            server.assignRequest(r);
        }
    }
    
    // check if we need to scale servers (only if enough time has passed since last adjustment)
    if (elapsedTime - lastServerAdjustment >= config.serverAdjustmentDelay) {
        int currentServers = servers.size();
        int queueSize = requestQueue.size();
        
        // scale up if queue is too large
        if (queueSize > config.queueHighThreshold * currentServers && currentServers < config.maxServers) {
            addServer();
            lastServerAdjustment = elapsedTime;
            std::cout << "[" << elapsedTime << "] Scaling UP: Added server (now " << servers.size() << " servers, queue: " << queueSize << ")" << std::endl;
        }
        // scale down if queue is too small (but keep at least 1 server)
        else if (queueSize < config.queueLowThreshold * currentServers && currentServers > 1) {
            // only remove if the server is idle
            if (servers.back().isIdle()) {
                removeServer();
                lastServerAdjustment = elapsedTime;
                std::cout << "[" << elapsedTime << "] Scaling DOWN: Removed server (now " << servers.size() << " servers, queue: " << queueSize << ")" << std::endl;
            }
        }
    }
    
    elapsedTime++;
}

Request LoadBalancer::getNextRequest() {
    Request r = requestQueue.front();
    requestQueue.pop();
    return r;
}

void LoadBalancer::addServer() {
    servers.push_back(Webserver(servers.size()));
}

void LoadBalancer::removeServer() {
    if (!servers.empty() && servers.back().isIdle()) {
        servers.pop_back();
    }
}

