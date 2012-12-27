#include "aircraftlanding.h"

#include <gecode/gist.hh>

#include "instance.h"

AircraftLanding::AircraftLanding(const char* filename) : instance(filename)
{
	aircraftTimes = IntVarArray(*this, instance.aircrafts.size(), 0, instance.periods);

	IntVar zero = IntVar(*this, 0,0); // helper variable

	IntVarArray aircraftLateAmount = IntVarArray(*this, instance.aircrafts.size(), 0, instance.periods);
	IntVarArray aircraftEarlyAmount = IntVarArray(*this, instance.aircrafts.size(), 0, instance.periods);


	for (uint i=0; i<instance.aircrafts.size(); i++) {
		Aircraft *curAircraft = instance.aircrafts[i];

		// aircraft times
		dom(*this, aircraftTimes[i], curAircraft->min, curAircraft->max);

		// delay is max ( time - preferred, 0 )
		// too soon is max ( preferred - time, 0 )
		max(*this, expr(*this, aircraftTimes[i] - curAircraft->preferred), zero, aircraftLateAmount[i]);
		max(*this, expr(*this, curAircraft->preferred - aircraftTimes[i]), zero, aircraftEarlyAmount[i]);
	}

	// costs
	const vector<int> earlyCostFactors = instance.getAircraftEarlyCosts();
	int maxEarly = instance.periods * (*std::max_element(earlyCostFactors.begin(), earlyCostFactors.end()));
	earlyCosts = IntVar(*this, 0, maxEarly);
	const vector<int> lateCostFactorss = instance.getAircraftLateCosts();
	int maxLate = (*std::max_element(lateCostFactorss.begin(), lateCostFactorss.end()));
	lateCosts = IntVar(*this, 0, instance.periods * maxLate);

	IntArgs aircraftEarlyCosts = IntArgs(instance.getAircraftEarlyCosts());
	IntArgs aircraftLateCosts = IntArgs(instance.getAircraftLateCosts());

	linear(*this, aircraftEarlyCosts, aircraftEarlyAmount, IRT_EQ, earlyCosts);
	linear(*this, aircraftLateCosts, aircraftLateAmount, IRT_EQ, lateCosts);

	branch(*this, aircraftTimes, INT_VAR_NONE, INT_VAL_MAX);
}

Space* AircraftLanding::copy(bool share)
{
	return new AircraftLanding(share, *this);
}

AircraftLanding::AircraftLanding(bool share, AircraftLanding& al) : MYSPACE(share, al), instance(al.instance)
{
	aircraftTimes.update(*this, share, al.aircraftTimes);
	//costVar.update(*this, share, al.costVar);
	earlyCosts.update(*this, share, al.earlyCosts);
	lateCosts.update(*this, share, al.lateCosts);
}

AircraftLanding::~AircraftLanding()
{
}

IntVar AircraftLanding::cost() const
{
	return expr(*const_cast<AircraftLanding*>(this), earlyCosts + lateCosts);
}

void AircraftLanding::print(ostream& os)
{
	os << "Solution: ";
	os << aircraftTimes << endl;
}



