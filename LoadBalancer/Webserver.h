/**
 * @file Webserver.h
 * @brief Web server class that processes requests
 * @date February 2026
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

/**
 * @class Webserver
 * @brief Simulates a web server that processes client requests
 * 
 * Each server can handle one request at a time. When assigned a request,
 * it becomes busy and processes it over multiple clock cycles.
 */
class Webserver {
private:
    Request currentRequest;  /**< Currently processing request */
    bool busy;               /**< True if server is processing a request */
    int remainingTime;       /**< Clock cycles remaining for current request */
    int id;                  /**< Unique server identifier */

public:
    /**
     * @brief Constructor for Webserver
     * @param id Unique identifier for this server
     */
    Webserver(int id);
    
    /**
     * @brief Check if server is idle (not busy)
     * @return True if server has no active request
     */
    bool isIdle();
    
    /**
     * @brief Process one clock cycle of work
     * Decrements remaining time if busy. Becomes idle when time reaches zero.
     */
    void tick();
    
    /**
     * @brief Assign a new request to this server
     * @param request The request to process
     */
    void assignRequest(const Request& request);
    
    /**
     * @brief Get the unique ID of this server
     * @return Server identifier
     */
    int getId() const;
};

#endif // WEBSERVER_H
