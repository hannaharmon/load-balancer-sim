#include "Webserver.h"
#include <iostream>

Webserver::Webserver(int id)
    : currentRequest("", "", 0, JobType::Processing), busy(false), remainingTime(0), id(id) {
}

bool Webserver::isIdle() {
    return !busy;
}

void Webserver::tick() {
    if (busy && remainingTime > 0) {
        remainingTime--;
        
        // check if request is complete
        if (remainingTime == 0) {
            busy = false;
        }
    }
}

void Webserver::assignRequest(const Request& request) {
    if (!busy) {
        currentRequest = request;
        remainingTime = request.time;
        busy = true;
    }
}

int Webserver::getId() const {
    return id;
}
