#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "Request.h"

class Webserver {
private:
    Request currentRequest;
    bool busy;
    int remainingTime;
    int id;

public:
    Webserver(int id);
    bool isIdle();
    void tick();
    void assignRequest(const Request& request);
    int getId() const;
};

#endif // WEBSERVER_H
