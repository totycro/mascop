#include "aircraftlanding.h"

#include <gecode/gist.hh>

#include "instance.h"

AircraftLanding::AircraftLanding(const char* filename) : instance(filename)
{
	aircraftTimes = IntVarArray(*this, instance.aircrafts.size(), 0, instance.periods);

	for (uint i=0; i<instance.aircrafts.size(); i++) {
		cerr << "min/max " <<
			instance.aircrafts[i]->min << " " <<
			instance.aircrafts[i]->max << endl;
		//rel(*this, aircraftTimes[i], IRT_GQ, instance.aircrafts[i]->min);
		//rel(*this, aircraftTimes[i], IRT_LQ, instance.aircrafts[i]->max);
		dom(*this, aircraftTimes[i], instance.aircrafts[i]->min, instance.aircrafts[i]->max);
		//rel(*this, aircraftTimes[i], IRT_GQ, 2);
	}
	costVar = IntVar(*this, 0, 1000);
	rel(*this, aircraftTimes[0], IRT_EQ, costVar);

	branch(*this, aircraftTimes, INT_VAR_NONE, INT_VAL_MAX);
}

Space* AircraftLanding::copy(bool share)
{
	return new AircraftLanding(share, *this);
}

AircraftLanding::AircraftLanding(bool share, AircraftLanding& al) : MYSPACE(share, al), instance(al.instance)
{
	aircraftTimes.update(*this, share, al.aircraftTimes);
	costVar.update(*this, share, al.costVar);
}

AircraftLanding::~AircraftLanding()
{
}

IntVar AircraftLanding::cost() const
{
	return costVar;
}

void AircraftLanding::print(ostream& os)
{
	os << "Solution: ";
	os << aircraftTimes << endl;
}



