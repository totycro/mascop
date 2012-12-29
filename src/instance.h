#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Instance {

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
	vector<unsigned int> unavailableStart, unavailableEnd;
};

struct Instance {
public:

	unsigned int periods;
	unsigned int max_landings_in_30_mins;
	vector<Aircraft*> aircrafts;
	vector<Runway*> runways;
	vector<vector< unsigned int > > sequenceDelays;

	Instance(const char* filename);

	const vector<int> getAircraftEarlyCosts() const;
	const vector<int> getAircraftLateCosts() const;

	void printInstance(ostream& os = std::cout);
};


}
#endif // INSTANCE_H