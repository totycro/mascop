#ifndef AIRCRAFTLANDING_H
#define AIRCRAFTLANDING_H

#include "instance.h"

#include <gecode/int.hh>

using namespace Gecode;

class AircraftLanding : public Space
{
	Instance instance;

public:
	AircraftLanding(const char* filename);
	AircraftLanding(bool share, AircraftLanding& al);
	virtual ~AircraftLanding();

};

#endif // AIRCRAFTLANDING_H
