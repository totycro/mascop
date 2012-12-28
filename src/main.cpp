#include <iostream>


#include "aircraftlanding.h"

int main(int argc, char **argv) {
	AircraftLanding * al;

	al = new AircraftLanding(argv[1]);

	/*
	try {
		al = new AircraftLanding(argv[1]);
	} catch (Gecode::Exception &e) {
		cerr << "exception: " << e.what() << endl;

		return 1;
	}
	*/

	{

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
		} else {
		}

	}

	if (false)
	{
		DFS<AircraftLanding> dfs(al);

		AircraftLanding * sol = dfs.next();

		if (sol) {
			sol->print(cerr);
		} else {
			cout << "No solution.\n";
		}
	}

	Instance(argv[1]).printInstance();

	return 0;
}
