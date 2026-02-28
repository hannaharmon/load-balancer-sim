/**
 * @file LoadBalancer.h
 * @brief Load balancer that manages request queue and server pool
 * @date February 2026
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <vector>
#include <queue>
#include "Request.h"
#include "Webserver.h"
#include "Firewall.h"
#include "Logger.h"

/**
 * @class LoadBalancer
 * @brief Manages request distribution and dynamic server scaling
 * 
 * The load balancer maintains a request queue and distributes requests to
 * available web servers. It dynamically scales the server pool based on
 * queue size thresholds (50-80 requests per server).
 */
class LoadBalancer {
private:
    std::queue<Request> requestQueue;  /**< FIFO queue of pending requests */
    std::vector<Webserver> servers;    /**< Pool of web servers */
    SimulationConfig config;           /**< Simulation configuration */
    Firewall firewall;                 /**< IP blocking firewall */
    int elapsedTime;                   /**< Current simulation clock cycle */
    int lastServerAdjustment;          /**< Last cycle when scaling occurred */
    Logger* logger;                    /**< Pointer to logging system */
    int scalingUpEvents;               /**< Count of server additions */
    int scalingDownEvents;             /**< Count of server removals */
    int blockedRequests;               /**< Count of firewall-blocked requests */

public:
    /**
     * @brief Constructor for LoadBalancer
     * @param config Simulation configuration parameters
     * @param numServers Initial number of servers to create
     * @param logger Pointer to logger for event tracking
     */
    LoadBalancer(const SimulationConfig& config, int numServers, Logger* logger);
    
    /**
     * @brief Get current size of request queue
     * @return Number of pending requests
     */
    int getQueueSize();
    
    /**
     * @brief Submit a new request to the load balancer
     * @param r Request to add to queue (if not blocked by firewall)
     */
    void sendRequest(const Request& r);
    
    /**
     * @brief Process one clock cycle of load balancing
     * Ticks all servers, distributes queued requests, handles dynamic scaling
     */
    void tick();
    
    /**
     * @brief Remove and return next request from queue
     * @return The next request to process
     */
    Request getNextRequest();
    
    /**
     * @brief Add a new server to the pool
     */
    void addServer();
    
    /**
     * @brief Remove an idle server from the pool
     */
    void removeServer();
    
    /**
     * @brief Get current number of active servers
     * @return Server count
     */
    int getServerCount() const;
    
    /**
     * @brief Get total scaling events (up + down)
     * @return Combined count of all scaling operations
     */
    int getScalingEvents() const;
    
    /**
     * @brief Get number of requests blocked by firewall
     * @return Count of blocked requests
     */
    int getBlockedRequests() const;
};

#endif // LOADBALANCER_H
