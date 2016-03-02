
#include <iostream>
#include <random>
#include "World.hpp"
#include <fstream>

void execute(ofstream& gen_file, ofstream& fac_file, int nb_simu, int nb_factions) {
	cout << "simulation a " << nb_factions << " factions" << endl;

	gen_file << "SIMULATION " << nb_factions << " FACTIONS" << endl;
	gen_file << "Nb tours ;" << "fac win ;" << "nb success;" << "nb fails ;" << "nb attacks" << endl;
	fac_file << "SIMULATION " << nb_factions << " FACTIONS" << endl;

	for (int i=0; i < nb_factions;i++) {
		fac_file << "Name ;" << "Death; " << "Money ;" << "Prod ;" << "Spent ;"
			<< "Nb colonies ;" << "Nb attacks ;" << "Nb success ;" << "Nb fails ;"
			<< "ML x;" << "ML y;" << "ML natdef;" << "ML natprod;" << "ML findef;" << "ML finprod;;";
	}
	fac_file << endl;

	for (int i = 0;i < nb_simu;i++) {
		World w;
		switch (nb_factions)
		{
		case 2:
			w.test2factions();
			break;
		case 3:
			w.test3factions();
			break;
		case 4:
			w.test4factions();
			break;
		default:
			cout << nb_factions << " : cas non valide" << endl;
			break;
		}
		cout << "debut simulation " << i << endl;
		w.start();
		gen_file << w.stats_general();
		fac_file << w.stats_faction();
		cout << "fin simulation " << i << endl;

		World::dispose();
	}
}

int main(int, char **) 
{
	ofstream gen_file("res.csv");
	ofstream fac_file("fac.csv");
	if (!gen_file || !fac_file) {
		cout << "fichier non initialise" << endl;
	}
	else {
		execute(gen_file,fac_file, 100, 2);
		execute(gen_file, fac_file, 100, 3);
		execute(gen_file, fac_file, 100, 4);
	}
	return 0;
}