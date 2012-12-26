#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>

using namespace std;

enum AircraftType { SMALL, MEDIUM, LARGE, NUMBER_OF_AIRCRAFT_TYPES };

AircraftType str2aircrafttype(const string& str);

struct Aircraft {
	string name;
	int min, preferred, max;
	AircraftType type;
	int lateCost, earlyCost;
};

struct Runway {
	string name;
	vector<int> unavailableStart, unavailableEnd;
};

struct Instance {
public:

	int periods;
	int max_landings_in_30_mins;
	vector<Aircraft*> aircrafts;
	vector<Runway*> runways;
	vector<vector< int > > sequenceDelays;


	Instance(const char* filename);
};
#endif // INSTANCE_H