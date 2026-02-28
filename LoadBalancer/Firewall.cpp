#include "Firewall.h"

Firewall::Firewall(const std::unordered_set<std::string>& blockedIPs)
    : blockedIPs(blockedIPs) {
}

bool Firewall::isBlocked(const std::string& ip) {
    return blockedIPs.find(ip) != blockedIPs.end();
}

void Firewall::blockIP(const std::string& ip) {
    blockedIPs.insert(ip);
}

void Firewall::unblockIP(const std::string& ip) {
    blockedIPs.erase(ip);
}
