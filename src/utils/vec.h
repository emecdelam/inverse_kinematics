#pragma once
#include <raymath.h>
#include "log.h"

void prVector3(Vector3 vec, const char* st){
    log_debug("Printing vector %s,%f,%f,%f\n",st,vec.x,vec.y,vec.z);
}