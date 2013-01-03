#ifndef AIRCRAFTLANDING_H
#define AIRCRAFTLANDING_H

#include "instance.h"

#include <gecode/int.hh>
#include <gecode/set.hh>
#include <gecode/minimodel.hh>
#include <gecode/search.hh>

using namespace Gecode;

#define MYSPACE MinimizeSpace

class AircraftLanding : public MYSPACE
{
	Instance::Instance instance;

	IntVarArray aircraftTimes;

	IntVarArray aircraftSequence;

	IntVarArray aircraftRunways;

	SetVarArray runwayAircrafts;

	SetVarArray timeAircrafts;

	IntVarArray timeRunwaysAircrafts;

	IntVar costVar;

	IntVarArray timesSequence;



public:
	AircraftLanding(const char* filename, int maxCost);
	AircraftLanding(bool share, AircraftLanding& al);
	virtual ~AircraftLanding();
	virtual Space* copy(bool share);

	virtual IntVar cost() const;

	virtual void print(ostream& os = std::cout, bool verbose=false) const;

};

#endif // AIRCRAFTLANDING_H
