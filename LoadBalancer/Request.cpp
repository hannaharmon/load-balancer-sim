#include "Request.h"

Request::Request(const std::string& inIP, const std::string& outIP, int time, JobType jobType)
    : inIP(inIP), outIP(outIP), time(time), jobType(jobType) {
}
