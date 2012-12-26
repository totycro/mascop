#include <iostream>

#include "aircraftlanding.h"

int main(int argc, char **argv) {
	AircraftLanding * al = new AircraftLanding(argv[1]);

	BAB<AircraftLanding> bab(al);

	AircraftLanding *sol;
	int i = 0;
	while ( (sol = bab.next()) ) {
		cout << "iter " << i << "\n";
		sol->print();
		i++;
	}

	if (bab.stopped()) {
		cout << "SUB optimal.\n";
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
