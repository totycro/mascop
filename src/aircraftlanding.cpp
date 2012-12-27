#include "aircraftlanding.h"

#include <gecode/gist.hh>

#include "instance.h"

AircraftLanding::AircraftLanding(const char* filename) : instance(filename)
{
	aircraftTimes = IntVarArray(*this, instance.aircrafts.size(), 0, instance.periods);

	IntVar zero = IntVar(*this, 0,0); // helper variable

	IntVarArray aircraftLateAmount = IntVarArray(*this, instance.aircrafts.size(), 0, instance.periods);
	IntVarArray aircraftEarlyAmount = IntVarArray(*this, instance.aircrafts.size(), 0, instance.periods);

	IntArgs aircraftEarlyCosts = IntArgs(instance.getAircraftEarlyCosts());
	IntArgs aircraftLateCosts = IntArgs(instance.getAircraftLateCosts());

	for (uint i=0; i<instance.aircrafts.size(); i++) {
		Aircraft *curAircraft = instance.aircrafts[i];

		cerr << "min/max " <<
			instance.aircrafts[i]->min << " " <<
			instance.aircrafts[i]->max << endl;
		dom(*this, aircraftTimes[i], curAircraft->min, curAircraft->max);

		// delay is max ( time - preferred, 0 )
		// too soon is max ( preferred - time, 0 )
		max(*this, expr(*this, aircraftTimes[i] - curAircraft->preferred), zero, aircraftLateAmount[i]);
		max(*this, expr(*this, curAircraft->preferred - aircraftTimes[i]), zero, aircraftEarlyAmount[i]);
	}

	const vector<int> earlyCostFactors = instance.getAircraftEarlyCosts();
	int maxEarly = instance.periods * (*std::max_element(earlyCostFactors.begin(), earlyCostFactors.end()));
	IntVar earlyCosts(*this, 0, maxEarly);
	const vector<int> lateCostFactorss = instance.getAircraftLateCosts();
	int maxLate = (*std::max_element(lateCostFactorss.begin(), lateCostFactorss.end()));
	IntVar lateCosts(*this, 0, instance.periods * maxLate);

	linear(*this, aircraftEarlyCosts, aircraftEarlyAmount, IRT_EQ, earlyCosts);
	linear(*this, aircraftLateCosts, aircraftLateAmount, IRT_EQ, lateCosts);

	costVar = IntVar(*this, 0, std::max(maxLate, maxEarly) * instance.aircrafts.size());
	rel(*this, costVar, IRT_EQ, expr(*this, earlyCosts + lateCosts));

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



