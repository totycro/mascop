#include "aircraftlanding.h"

#include <gecode/gist.hh>
#include <gecode/set.hh>
#include <gecode/int.hh>
#include <gecode/set/sequence.hh>

#include <fstream>

#include "instance.h"

AircraftLanding::AircraftLanding(const char* filename) : instance(filename)
{
	unsigned int aircraftsNum = instance.aircrafts.size();
	unsigned int runwaysNum = instance.runways.size();

	aircraftTimes = IntVarArray(*this, aircraftsNum, 0, instance.periods-1);
	aircraftRunways = IntVarArray(*this, aircraftsNum, 0, runwaysNum-1);

	aircraftSequence = IntVarArray(*this, aircraftsNum, 0, aircraftsNum-1);
	/*
	distinct(*this, aircraftSequence);
	//nvalues(*this, aircraftSequence, IRT_EQ, aircraftsNum);


	for (unsigned int i=0; i<aircraftsNum; i++) {
		for (unsigned int j=0; j<aircraftsNum; j++) {
			if (j == i) {
				continue;
			}

			BoolVar isBefore = expr(*this, aircraftTimes[i] < aircraftTimes[j]);

			IntVar iIndex(*this, 0, aircraftsNum-1);
			IntVar jIndex(*this, 0, aircraftsNum-1);
			element(*this, aircraftSequence, iIndex, i);
			element(*this, aircraftSequence, jIndex, j);

			BoolVar isSeqBefore = expr(*this, iIndex < jIndex);

			//rel(*this, isBefore >> isSeqBefore);
		}
	}

	int * s = new int[3];
	s[0] = 5;
	s[1] = 0;
	s[2] = 3;
	sequence(*this, aircraftSequence, IntSet(s, 3), 5, 0, 1);
	*/


	//runwayAircrafts = SetVarArray(*this, runwaysNum,  IntSet::empty, IntSet(0, aircraftsNum-1), 0, aircraftsNum);
	//channel(*this, aircraftRunways, runwayAircrafts);

	IntVar zero = IntVar(*this, 0,0); // helper variable

	{
		IntVarArray aircraftLateAmount = IntVarArray(*this, aircraftsNum, 0, instance.periods-1);
		IntVarArray aircraftEarlyAmount = IntVarArray(*this, aircraftsNum, 0, instance.periods-1);

		for (uint i=0; i<aircraftsNum; i++) {
			Instance::Aircraft *curAircraft = instance.aircrafts[i];

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

	timeRunwaysAircrafts = IntVarArray(*this, instance.periods * runwaysNum, -1, aircraftsNum); // allow unassigned


	// 3-dimensional repr:

	for (uint i=0; i<aircraftsNum; i++) {
		IntVar iVar(*this, i, i);
		// gecode fail, doesn't suport as matrix, but this:
		element(*this, timeRunwaysAircrafts, expr(*this, (aircraftRunways[i]*instance.periods) + aircraftTimes[i]), iVar);
	}

	IntVar varInvalid(*this, -1, -1);

	// unused spaces are -1
	count(*this, timeRunwaysAircrafts, varInvalid, IRT_EQ, timeRunwaysAircrafts.size() - aircraftsNum);

	// runway limitations
	for (uint i=0; i<runwaysNum; i++) {
		Instance::Runway *rw = instance.runways[i];

		for (uint j=0; j<rw->unavailableStart.size(); j++) {

			for (uint k=rw->unavailableStart[j]; k<rw->unavailableEnd[j]; k++) {
				//cout << "deact: " << (<< endl;
				element(*this, timeRunwaysAircrafts, expr(*this, (i*instance.periods) +  k), varInvalid);
			}
		}
	}

	// sets for each period with aircrafts that land then (all runways)
	timeAircrafts = SetVarArray(*this, instance.periods, IntSet::empty, IntSet(0, aircraftsNum), 0, runwaysNum);
	for (uint i=0; i<aircraftsNum; i++) {
		SetVar timeSet = SetVar(*this);
		element(*this, timeAircrafts, aircraftTimes[i], timeSet);
		rel(*this, singleton(i) <= timeSet);
	}

	// max landings
	for (unsigned int i=0; i+30<instance.periods; i++) {

			SetVar uni(*this, IntSet::empty, IntSet(0, aircraftsNum), 0, instance.max_landings_in_30_mins);
			//SetVar uni(*this);
			for (unsigned int j=0; j<30; j++) {
				rel(*this, timeAircrafts[i+j], SRT_SUB, uni);
				//rel(*this, timeAircrafts[i+j] <= uni);
			}
			//cardinality(*this, uni, IRT_LQ, instance.max_landings_in_30_mins);

		}
	//}

	int noOv = 0;
	int noOvDel = 0;
	int all = 0;
	for (unsigned int i=0; i<aircraftsNum; i++) {
		for (unsigned int j=i+1; j<aircraftsNum; j++) {
			if (j == i) {
				continue;
			}

			int minDelay_ij = instance.sequenceDelays[instance.aircrafts[i]->type][instance.aircrafts[j]->type];
			int minDelay_ji = instance.sequenceDelays[instance.aircrafts[j]->type][instance.aircrafts[i]->type];

			Instance::Aircraft *ai = instance.aircrafts[i];
			Instance::Aircraft *aj = instance.aircrafts[j];

			if (ai->max < aj->min || ai->min > aj->max) {
				noOv++;
			}

			if (ai->max + minDelay_ij < aj->min || ai->min > aj->max + minDelay_ji) {
				noOvDel++;
			}
			all++;
		}
	}

	ofstream f("/tmp/dat.dump", ios::trunc);
	f << "all: " << all << endl;
	f << "noOv: " << noOv << endl;
	f << "noOvDel: " << noOvDel << endl;

	// depending on type, two airplanes have to have to be scheduled a few periods apart
	// (this also prevents planes landing at the same time)
#if 0
	for (unsigned int i=0; i<aircraftsNum; i++) {
		for (unsigned int j=0; j<aircraftsNum; j++) {
			if (j == i) {
				continue;
			}

			// get minimum gap depending on type (statically known)
			int minDelay = instance.sequenceDelays[instance.aircrafts[i]->type][instance.aircrafts[j]->type];

			BoolVar sameRunway = expr(*this, aircraftRunways[i] == aircraftRunways[j]);

			BoolVar isBefore = expr(*this, aircraftTimes[i] < aircraftTimes[j]);

			BoolVar maintainsDelay = expr(*this, aircraftTimes[i] + minDelay <= aircraftTimes[j]);

			rel(*this, (sameRunway && isBefore) >> maintainsDelay  );
			//rel(*this, isBefore >> maintainsDelay  );
			//rel(*this, !(sameRunway && isBefore && (!maintainsDelay) ) );
		}
	}
#endif

#define delay_old 1

// same as above, but less constraints
#if delay_old
	for (unsigned int i=0; i<aircraftsNum; i++) {
		for (unsigned int j=i+1; j<aircraftsNum; j++) {


			// get minimum gap depending on type (statically known)
			//int minDelay = instance.sequenceDelays[instance.aircrafts[i]->type][instance.aircrafts[j]->type];
			int minDelay_ij = instance.sequenceDelays[instance.aircrafts[i]->type][instance.aircrafts[j]->type];
			int minDelay_ji = instance.sequenceDelays[instance.aircrafts[j]->type][instance.aircrafts[i]->type];

			Instance::Aircraft *ai = instance.aircrafts[i];
			Instance::Aircraft *aj = instance.aircrafts[j];

			if (ai->max + minDelay_ij < aj->min || ai->min > aj->max + minDelay_ji) {
				continue; // no overlap possible
			}

			BoolVar sameRunway = expr(*this, aircraftRunways[i] == aircraftRunways[j]);

			//BoolVar isBefore = expr(*this, aircraftTimes[i] < aircraftTimes[j]);

			BoolVar isBefore_ij = expr(*this, aircraftTimes[i] < aircraftTimes[j]);
			//BoolVar isBefore_ji = expr(*this, aircraftTimes[j] < aircraftTimes[i]);

			//BoolVar maintainsDelay = expr(*this, aircraftTimes[i] + minDelay <= aircraftTimes[j]);

			BoolVar maintainsDelay_ij = expr(*this, aircraftTimes[i] + minDelay_ij <= aircraftTimes[j]);
			BoolVar maintainsDelay_ji = expr(*this, aircraftTimes[j] + minDelay_ji <= aircraftTimes[i]);

			//rel(*this, !sameRunway || ( ( isBefore_ij >> maintainsDelay_ij ) && ( isBefore_ji >> maintainsDelay_ji) ) );
			rel(*this, !sameRunway || ( ( isBefore_ij && maintainsDelay_ij )  || maintainsDelay_ji ) );
			//rel(*this, !sameRunway || ( isBefore_ij && maintainsDelay_ij )  || maintainsDelay_ji ) );
		}
	}
#endif

	//better, with index to next runway overlap problem
#if ! delay_old
		for (unsigned int i=0; i<aircraftsNum; i++) {
			for (unsigned int j=i+1; j<aircraftsNum; j++) {
				int minDelay_ij = instance.sequenceDelays[instance.aircrafts[i]->type][instance.aircrafts[j]->type];
				int minDelay_ji = instance.sequenceDelays[instance.aircrafts[j]->type][instance.aircrafts[i]->type];

				/*
				IntVar iPos = expr(*this, (aircraftRunways[i]*instance.periods) + aircraftTimes[i]);
				IntVar jPos = expr(*this, (aircraftRunways[j]*instance.periods) + aircraftTimes[j]);
				*/

				BoolVar sameRunway = expr(*this, aircraftRunways[i] == aircraftRunways[j]);


				IntVar iPos(*this, 0, runwaysNum*instance.periods);
				IntVar jPos(*this, 0, runwaysNum*instance.periods);
				element(*this, timeRunwaysAircrafts, iPos, i);
				element(*this, timeRunwaysAircrafts, jPos, j);

				BoolVar isBefore_ij = expr(*this, iPos < jPos);

				BoolVar maintainsDelay_ij = expr(*this, iPos + minDelay_ij <= jPos);
				BoolVar maintainsDelay_ji = expr(*this, jPos + minDelay_ji <= iPos);

				//cerr << "p " << minDelay_ij << " " << minDelay_ji << endl;

				//rel(*this, (!sameRunway) || maintainsDelay_ij || maintainsDelay_ji);
			rel(*this, ( ( isBefore_ij && maintainsDelay_ij )  || maintainsDelay_ji ) );
			}
		}
#endif

	//branch(*this, aircraftTimes, INT_VAR_DEGREE_MIN, INT_VAL_SPLIT_MIN);
	//branch(*this, aircraftTimes, INT_VAR_NONE, INT_VAL_RANGE_MAX);
	//branch(*this, aircraftTimes, INT_VAR_DEGREE_MIN, INT_VAL_SPLIT_MIN);
	//branch(*this, aircraftTimes, INT_VAR_AFC_MAX, INT_VAL_SPLIT_MIN);
	//branch(*this, aircraftTimes, INT_VAR_AFC_MAX, INT_VAL_MAX);
	//branch(*this, aircraftTimes, INT_VAR_NONE, INT_VAL_SPLIT_MIN);

	//branch(*this, aircraftTimes, INT_VAR_AFC_MAX, INT_VAL_MED);
	//branch(*this, aircraftTimes, INT_VAR_DEGREE_MAX, INT_VAL_MED);
	branch(*this, aircraftTimes, INT_VAR_SIZE_MIN, INT_VAL_MED);

	//branch(*this, aircraftTimes, INT_VAR_DEGREE_MIN, INT_VAL_RND);
	//branch(*this, aircraftSequence, INT_VAR_DEGREE_MIN, INT_VAL_SPLIT_MIN);
	//branch(*this, aircraftTimes, INT_VAR_NONE, INT_VAL_SPLIT_MIN);
	branch(*this, aircraftRunways, INT_VAR_AFC_MAX, INT_VAL_MAX);
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
	//runwayAircrafts.update(*this, share, al.runwayAircrafts);
	timeAircrafts.update(*this, share, al.timeAircrafts);

	timeRunwaysAircrafts.update(*this, share, al.timeRunwaysAircrafts);

	aircraftSequence.update(*this, share, al.aircraftSequence);
}

AircraftLanding::~AircraftLanding()
{
}

IntVar AircraftLanding::cost() const
{
	return costVar;
}

void AircraftLanding::print(ostream& os, bool verbose) const
{
	os << "Solution: (cost: " << cost().min() << "," << cost().max() << ") "<<endl;
	os << "Times: " << aircraftTimes << endl;
	os << "Runways: " << aircraftRunways << endl;

		for (unsigned int i=0; i<instance.runways.size(); i++) {
			os << "timeair rw " << i << ": " << ((IntVarArray)(timeRunwaysAircrafts)).slice(i*instance.periods, 1, (i+1) *instance.periods) << endl;
		}
	//os << "timeair: " << timeAircrafts << endl;
	return;
	//os << "Runways2: " << runwayAircrafts << endl;
	os << "seq: " << aircraftSequence << endl;


	if (verbose) {
		os << "timeair: " << timeAircrafts << endl;
		for (unsigned int i=0; i<instance.runways.size(); i++) {
			os << "timeair rw " << i << ": " << ((IntVarArray)(timeRunwaysAircrafts)).slice(i*instance.periods, 1, (i+1) *instance.periods) << endl;
		}

		/*
		for (unsigned int i=0; i<timeAircraftsRunways.size(); i++) {
			os << "timeair " << i << ": " << timeAircraftsRunways[i] << endl;
		}
		*/
	} else {
		os << "verbose deactivated, skipping timeair\n";
	}
}



