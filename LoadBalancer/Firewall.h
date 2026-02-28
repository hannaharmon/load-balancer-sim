#ifndef FIREWALL_H
#define FIREWALL_H

#include <string>
#include <unordered_set>

class Firewall {
private:
    std::unordered_set<std::string> blockedIPs;

public:
    Firewall(const std::unordered_set<std::string>& blockedIPs);
    bool isBlocked(const std::string& ip);
    void blockIP(const std::string& ip);
    void unblockIP(const std::string& ip);
};

#endif // FIREWALL_H
