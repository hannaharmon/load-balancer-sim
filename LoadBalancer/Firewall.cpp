/**
 * @file Firewall.cpp
 * @brief Implementation of Firewall class with CIDR support
 * @date February 2026
 */

#include "Firewall.h"
#include <sstream>

Firewall::Firewall(const std::unordered_set<std::string>& blockedIPs)
    : blockedIPs(blockedIPs) {
    // Parse CIDR ranges from the blocked IPs set
    for (const auto& entry : blockedIPs) {
        size_t slashPos = entry.find('/');
        if (slashPos != std::string::npos) {
            // This is a CIDR range
            std::string ipPart = entry.substr(0, slashPos);
            int prefixLen = std::stoi(entry.substr(slashPos + 1));
            
            IPRange range;
            range.network = ipToInt(ipPart);
            range.mask = (prefixLen == 0) ? 0 : (~0u << (32 - prefixLen));
            range.network &= range.mask; // Normalize network address
            
            blockedRanges.push_back(range);
        }
    }
}

unsigned int Firewall::ipToInt(const std::string& ip) {
    std::istringstream iss(ip);
    unsigned int result = 0;
    std::string octet;
    int shift = 24;
    
    while (std::getline(iss, octet, '.') && shift >= 0) {
        result |= (std::stoi(octet) << shift);
        shift -= 8;
    }
    
    return result;
}

bool Firewall::isInRange(const std::string& ip) {
    unsigned int ipInt = ipToInt(ip);
    
    for (const auto& range : blockedRanges) {
        if ((ipInt & range.mask) == range.network) {
            return true;
        }
    }
    
    return false;
}

bool Firewall::isBlocked(const std::string& ip) {
    // Check exact match first
    if (blockedIPs.find(ip) != blockedIPs.end()) {
        return true;
    }
    
    // Check CIDR ranges
    return isInRange(ip);
}

void Firewall::blockIP(const std::string& ip) {
    blockedIPs.insert(ip);
}

void Firewall::unblockIP(const std::string& ip) {
    blockedIPs.erase(ip);
}
