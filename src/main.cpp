#include <iostream>


#include "aircraftlanding.h"

#include <gecode/gist.hh>

int main(int argc, char **argv) {
	AircraftLanding * al;

	al = new AircraftLanding(argv[1], -1);

	bool gist = false;
	bool idfs = false;

	if (argc > 2) {
		if (string(argv[2]) == "gist") {
			gist = true;
		} else if (string(argv[2]) == "idfs") {
			idfs = true;
		} else {
			cerr << "invalid parameter: " << argv[2] << endl;
			exit(1);
		}
	}

	/*
	try {
		al = new AircraftLanding(argv[1]);
	} catch (Gecode::Exception &e) {
		cerr << "exception: " << e.what() << endl;

		return 1;
	}
	*/

	if (gist) {
		Gist::Print<AircraftLanding> p("al");
		Gist::Options o;
		o.inspect.click(&p);
		Gist::bab(al,o);
		return 0;
	}

	if (idfs)
	{
		cout << "running iterative dfs\n";
		bool found = false;
		int limit = 2;

		while (!found) {
			delete al;

			cerr << "running with limit " << limit  << endl;
			al = new AircraftLanding(argv[1], limit);

			DFS<AircraftLanding> dfs(al);

			AircraftLanding * sol = dfs.next();

			found = sol;

			if (found) {
				cerr << "found: \n";
				sol->print(cerr);
			} else {
				if (limit < 10) {
					limit += 5;
				} else {
					limit += 10;
				}
			}
		}
		return 0;
	}

	if (true)
	{
		cout << "running bab\n";

		BAB<AircraftLanding> bab(al);


		AircraftLanding *sol, *lastSol=0;
		int i = 0;

		while ( (sol = bab.next()) ) {
			cout << "iter " << i << "\n";
			sol->print();
			lastSol = sol;
			i++;
		}

		if (lastSol != 0) {
			cerr << "\nwinner:\n";
			lastSol->print(cerr, true);
		} else {
			cerr << "\nno solution.\n";
		}


		if (bab.stopped()) {
			cout << "SUB optimal.\n";
		} else {
		}

		Search::Statistics stats = bab.statistics();

		cout << endl << "Stats:\n";
		cout << "expanded: " << stats.node << endl;
		cout << "failed: " << stats.fail << endl;
		cout << "depth: " << stats.depth << endl;
		cout << "propagate: " << stats.propagate << endl;

	}


	if (false)
	{
		cout << "running dfs\n";
		DFS<AircraftLanding> dfs(al);

		AircraftLanding * sol = dfs.next();

		if (sol) {
			sol->print(cerr);
		} else {
			cout << "No solution.\n";
		}
	}

	cout << endl;
	Instance::Instance(argv[1]).printInstance();

	return 0;
}
