/**
 * @file Request.cpp
 * @brief Implementation of Request struct
 * @date February 2026
 */

#include "Request.h"

Request::Request(const std::string& inIP, const std::string& outIP, int time, JobType jobType)
    : inIP(inIP), outIP(outIP), time(time), jobType(jobType) {
}
