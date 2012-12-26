#ifndef AIRCRAFTLANDING_H
#define AIRCRAFTLANDING_H

#include "instance.h"

class AircraftLanding
{
	Instance instance;

public:
	AircraftLanding(const char* filename);
	AircraftLanding(bool share, AircraftLanding& al);
	virtual ~AircraftLanding();

};

#endif // AIRCRAFTLANDING_H
