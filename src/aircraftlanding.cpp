#include "aircraftlanding.h"

#include "instance.h"

AircraftLanding::AircraftLanding(const char* filename) : instance(filename)
{

}
AircraftLanding::AircraftLanding(bool share, AircraftLanding& al) : instance(al.instance)
{

}
AircraftLanding::~AircraftLanding()
{

}

