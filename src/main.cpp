#include <iostream>

#include "aircraftlanding.h"

int main(int argc, char **argv) {
	AircraftLanding * al = new AircraftLanding(argv[1]);

	BAB<AircraftLanding> bab(al);

	AircraftLanding *sol;
	while ( (sol = bab.next()) ) {
		sol->print();
	}

	/*
	DFS<AircraftLanding> dfs(al);

	AircraftLanding * sol = dfs.next();

	if (sol) {
		sol->print(cerr);
	} else {
		cout << "No solution.\n";
	}
	*/

	return 0;
}
