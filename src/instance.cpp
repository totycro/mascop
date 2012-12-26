#include "instance.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

AircraftType str2aircrafttype(const string& str)
{
	if (str == "small") {
		return SMALL;
	} else if (str == "medium") {
		return MEDIUM;
	} else if (str == "large") {
		return LARGE;
	}
	throw new runtime_error("unexpected aircraft type: " + str);
}


Instance::Instance(const char* filename)
{

	bool readDbg = true;

	if (readDbg) cerr << "reading " << filename << endl;

	ifstream ifs( filename );
	if( ! ifs ) {
		cerr << "could not open input file " << filename << "\n";
		exit( -1 );
	}

	string unused;

	int aircraftsNum;

	ifs >> unused ; // Aircrafts:
	ifs >> aircraftsNum;

	int runwaysNum;
	ifs >> unused ; // Runways:
	ifs >> runwaysNum;

	ifs >> unused ; // Periods:
	ifs >> periods;

	ifs >> unused ; // max:
	ifs >> max_landings_in_30_mins;

	if (readDbg) cerr << "aircrafts: " << aircraftsNum << "; runways: " << runwaysNum << "; periods: " << periods << "; max landings in 30 mins: " << max_landings_in_30_mins << endl;

	ifs >> unused ; // aircraft spec:

	for (int i=0; i<aircraftsNum; i++) {
		Aircraft *ac = new Aircraft();
		ifs >> ac->name;
		string typeStr;
		ifs >> typeStr;
		ac->type = str2aircrafttype(typeStr);
		ifs >> ac->min;
		ifs >> ac->preferred;
		ifs >> ac->max;
		ifs >> ac->earlyCost;
		ifs >> ac->lateCost;

		if (readDbg) cerr << "aircraft " << ac->name << endl;

		aircrafts.push_back(ac);
	}

	ifs >> unused; // runway spec

	for (int i=0; i<runwaysNum; i++) {
		Runway *rw = new Runway();
		ifs >> rw->name;
		int unavailableCnt;
		ifs >> unavailableCnt;

		for (int j=0; j<unavailableCnt; j++) {
			int start, end;
			ifs >> start >> end;
			rw->unavailableStart.push_back(start);
			rw->unavailableEnd.push_back(end);
		}

		if (readDbg) cerr << "read runway " << rw->name << endl;

		runways.push_back(rw);
	}

	ifs >> unused; // seq del

	sequenceDelays.resize(NUMBER_OF_AIRCRAFT_TYPES);
	for (int i=0; i<NUMBER_OF_AIRCRAFT_TYPES; i++) {
		sequenceDelays[i].resize(NUMBER_OF_AIRCRAFT_TYPES);
	}

	for (int i=0; i<NUMBER_OF_AIRCRAFT_TYPES * NUMBER_OF_AIRCRAFT_TYPES; i++) {
		string t1, t2;
		int delay;
		ifs >> t1 >> t2 >> delay;

		sequenceDelays[ str2aircrafttype(t1) ] [ str2aircrafttype(t2) ] = delay;
	}

	if (readDbg) cerr << "m-m delay: " << sequenceDelays[1][1] << endl;
	if (readDbg) cerr << "l-l delay: " << sequenceDelays[2][0] << endl;
}

const std::vector< int > Instance::getAircraftEarlyCosts() const
{
	vector<int> res(aircrafts.size());
	for (unsigned int i=0; i<aircrafts.size(); i++) {
		res[i] = aircrafts[i]->earlyCost;
	}
	return res;
}

const std::vector< int > Instance::getAircraftLateCosts() const
{
	vector<int> res(aircrafts.size());
	for (unsigned int i=0; i<aircrafts.size(); i++) {
		res[i] = aircrafts[i]->lateCost;
	}
	return res;
}



