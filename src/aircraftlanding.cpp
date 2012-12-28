#include "aircraftlanding.h"

#include <gecode/gist.hh>
#include <gecode/set.hh>
#include <gecode/int.hh>

#include "instance.h"

AircraftLanding::AircraftLanding(const char* filename) : instance(filename)
{
	unsigned int aircraftsNum = instance.aircrafts.size();
	unsigned int runwaysNum = instance.runways.size();

	aircraftTimes = IntVarArray(*this, aircraftsNum, 0, instance.periods-1);
	aircraftRunways = IntVarArray(*this, aircraftsNum, 0, runwaysNum-1);

	runwayAircrafts = SetVarArray(*this, runwaysNum,  IntSet::empty, IntSet(0, aircraftsNum-1), 0, aircraftsNum);
	channel(*this, aircraftRunways, runwayAircrafts);

	IntVar zero = IntVar(*this, 0,0); // helper variable

	{
		IntVarArray aircraftLateAmount = IntVarArray(*this, aircraftsNum, 0, instance.periods-1);
		IntVarArray aircraftEarlyAmount = IntVarArray(*this, aircraftsNum, 0, instance.periods-1);

		for (uint i=0; i<aircraftsNum; i++) {
			Aircraft *curAircraft = instance.aircrafts[i];

			dom(*this, aircraftTimes[i], curAircraft->min, curAircraft->max);

			// delay is max ( time - preferred, 0 )
			// too soon is max ( preferred - time, 0 )
			max(*this, expr(*this, aircraftTimes[i] - curAircraft->preferred), zero, aircraftLateAmount[i]);
			max(*this, expr(*this, curAircraft->preferred - aircraftTimes[i]), zero, aircraftEarlyAmount[i]);
		}


		// setup cost
		{
			// deduce bounds
			const vector<int> earlyCostFactors = instance.getAircraftEarlyCosts();
			int maxEarly = instance.periods * (*std::max_element(earlyCostFactors.begin(), earlyCostFactors.end()));
			IntVar earlyCosts(*this, 0, maxEarly);
			const vector<int> lateCostFactorss = instance.getAircraftLateCosts();
			int maxLate = (*std::max_element(lateCostFactorss.begin(), lateCostFactorss.end()));
			IntVar lateCosts(*this, 0, instance.periods * maxLate);

			IntArgs aircraftEarlyCosts = IntArgs(instance.getAircraftEarlyCosts());
			IntArgs aircraftLateCosts = IntArgs(instance.getAircraftLateCosts());
			// "assignment"
			linear(*this, aircraftEarlyCosts, aircraftEarlyAmount, IRT_EQ, earlyCosts);
			linear(*this, aircraftLateCosts, aircraftLateAmount, IRT_EQ, lateCosts);

			costVar = IntVar(*this, 0, std::max(maxLate, maxEarly) * instance.aircrafts.size());
			rel(*this, costVar, IRT_EQ, expr(*this, earlyCosts + lateCosts));
		}
	}

	timeAircrafts = SetVarArray(*this, instance.periods, IntSet::empty, IntSet(0, aircraftsNum), 0, runwaysNum);
	for (uint i=0; i<aircraftsNum; i++) {
		SetVar timeSet = SetVar(*this);
		element(*this, timeAircrafts, aircraftTimes[i], timeSet);
		rel(*this, singleton(i) <= timeSet);
	}

	// max landings
	for (int i=0; i+30<instance.periods; i++) {

		IntVarArray noElems(*this, 30, 0, aircraftsNum);

		for (int j=0; j<30; j++) {
			cardinality(*this, timeAircrafts[i+j], noElems[j]);
		}

		rel(*this, sum(noElems) < instance.max_landings_in_30_mins);
	}

	// depending on type, two airplanes have to have to be scheduled a few periods apart
	// (this also prevents planes landing at the same time)
	for (uint i=0; i<aircraftsNum; i++) {
		for (uint j=0; j<aircraftsNum; j++) {
			if (j == i) {
				continue;
			}

			// get minimum gap depending on type (statically known)
			int minDelay = instance.sequenceDelays[instance.aircrafts[i]->type][instance.aircrafts[j]->type];

			BoolVar sameRunway = expr(*this, aircraftRunways[i] == aircraftRunways[j]);

			BoolVar isBefore = expr(*this, aircraftTimes[i] <= aircraftTimes[j]);

			BoolVar maintainsDelay = expr(*this, aircraftTimes[i] + minDelay < aircraftTimes[j]);

			//rel(*this, (sameRunway && isBefore) >> maintainsDelay  );
			//rel(*this, !(sameRunway && isBefore && (!maintainsDelay) ) );
		}
	}

	branch(*this, aircraftTimes, INT_VAR_DEGREE_MIN, INT_VAL_SPLIT_MIN);
	//branch(*this, aircraftTimes, INT_VAR_NONE, INT_VAL_SPLIT_MIN);
	branch(*this, aircraftRunways, INT_VAR_NONE, INT_VAL_SPLIT_MIN);
}

Space* AircraftLanding::copy(bool share)
{
	return new AircraftLanding(share, *this);
}

AircraftLanding::AircraftLanding(bool share, AircraftLanding& al) : MYSPACE(share, al), instance(al.instance)
{
	aircraftTimes.update(*this, share, al.aircraftTimes);
	costVar.update(*this, share, al.costVar);
	aircraftRunways.update(*this, share, al.aircraftRunways);
	runwayAircrafts.update(*this, share, al.runwayAircrafts);
	timeAircrafts.update(*this, share, al.timeAircrafts);
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
	os << "Solution: (cost: " << cost().val() << ") "<<endl;
	os << "Times: " << aircraftTimes << endl;
	os << "Runways: " << aircraftRunways << endl;
	os << "Runways2: " << runwayAircrafts << endl;
	os << "timeair: " << timeAircrafts << endl;
}



