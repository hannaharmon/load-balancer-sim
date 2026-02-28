/**
 * @file Firewall.h
 * @brief IP-based firewall with CIDR range support
 * @date February 2026
 */

#ifndef FIREWALL_H
#define FIREWALL_H

#include <string>
#include <unordered_set>
#include <vector>

/**
 * @struct IPRange
 * @brief Represents a CIDR network range for IP blocking
 */
struct IPRange {
    unsigned int network;  /**< Network address (binary) */
    unsigned int mask;     /**< Subnet mask (binary) */
};

/**
 * @class Firewall
 * @brief IP-based firewall for blocking malicious requests
 * 
 * Supports exact IP matching and CIDR notation (e.g., 192.168.0.0/16).
 * Used for DDoS prevention and access control.
 */
class Firewall {
private:
    std::unordered_set<std::string> blockedIPs;  /**< Exact IP addresses to block */
    std::vector<IPRange> blockedRanges;          /**< CIDR ranges to block */
    
    /**
     * @brief Convert dotted-decimal IP to 32-bit integer
     * @param ip IP address string (e.g., "192.168.1.1")
     * @return Binary representation of IP
     */
    unsigned int ipToInt(const std::string& ip);
    
    /**
     * @brief Check if IP falls within any blocked CIDR range
     * @param ip IP address to check
     * @return True if IP matches a blocked range
     */
    bool isInRange(const std::string& ip);

public:
    /**
     * @brief Constructor for Firewall
     * @param blockedIPs Set of IPs/CIDR ranges to block
     */
    Firewall(const std::unordered_set<std::string>& blockedIPs);
    
    /**
     * @brief Check if an IP is blocked
     * @param ip IP address to check
     * @return True if IP is blocked (exact match or in CIDR range)
     */
    bool isBlocked(const std::string& ip);
    
    /**
     * @brief Add an IP to the firewall block list
     * @param ip IP address or CIDR range to block
     */
    void blockIP(const std::string& ip);
    
    /**
     * @brief Remove an IP from the block list
     * @param ip IP address to unblock
     */
    void unblockIP(const std::string& ip);
};

#endif // FIREWALL_H
