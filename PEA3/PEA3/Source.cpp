#include <iostream>
#include "Menu.h"
#include <ctime>
#include <sstream>;
#include "TimeMeasure.h"

using namespace std;

void testy(int metoda, int time, int wierzcholki, float krzyzowanie);

EvolutionAlgorithm evolution;
vector<double> wyniki;
vector<vector<int>> drogi;
TimeMeasure pomiary;

int main()
{
	srand(time(NULL));
	//Menu menu; //Tworze sobie obiektklasy menu, z którego potem steruje programem
	//menu.mainMenu();

	Graph graf;
	evolution.setMutation(0.01);
	evolution.setStartPopulation(30);


	graf.createGiven("ftv170.atsp", 171);
	evolution.setGraph(graf);
	testy(2, 32, 171, 0.7);
	testy(2, 32, 171, 0.9);


	graf.createGiven("rbg403.atsp", 403);
	evolution.setGraph(graf);
	testy(1, 8, 403, 0.5);
	testy(1, 8, 403, 0.7);
	testy(1, 8, 403, 0.9);
	testy(1, 16, 403, 0.5);
	testy(1, 16, 403, 0.7);
	testy(1, 16, 403, 0.9);
	testy(1, 32, 403, 0.5);
	testy(1, 32, 403, 0.7);
	testy(1, 32, 403, 0.9);
	testy(2, 8, 403, 0.5);
	testy(2, 8, 403, 0.7);
	testy(2, 8, 403, 0.9);
	testy(2, 16, 403, 0.5);
	testy(2, 16, 403, 0.7);
	testy(2, 16, 403, 0.9);
	testy(2, 32, 403, 0.5);
	testy(2, 32, 403, 0.7);
	testy(2, 32, 403, 0.9);

	exit(EXIT_SUCCESS);
}

void testy(int metoda, int time, int wierzcholki, float krzyzowanie)
{
	evolution.setStop(time);
	evolution.setMutationMethod(metoda);
	evolution.setCrossing(krzyzowanie);
	ostringstream ss, ss1, ss2, ss3;
	ss << metoda;
	ss1 << wierzcholki;
	ss2 << time;
	ss3 << krzyzowanie;
	string nazwaPlikuAlgorytm = "Metoda " + ss.str() + " Wierzcholki-" + ss1.str() + "Krzyzowanie " + ss3.str() + "Wyniki-Czas = " + ss2.str() + ".txt";
	string nazwaPlikuDrogi = "Metoda " + ss.str() + " Wierzcholki-" + ss1.str() + "Krzyzowanie " + ss3.str() + "Drogi-Czas = " + ss2.str() + ".txt";
	for (int i = 0; i < 10; i++)
	{
		evolution.simulatingEvolution();
		wyniki.push_back(evolution.getPathCost());
		drogi.push_back(evolution.getPath());
		cout << "Policzone " << i + 1 << " dla grafu - " << wierzcholki << " Krzyzowanie - " << krzyzowanie << " Metoda - " << metoda << " Czas - " << time << endl;
	}
	pomiary.saveToFile(wyniki, nazwaPlikuAlgorytm);
	pomiary.saveToFile(drogi, nazwaPlikuDrogi);
	wyniki.clear();
	drogi.clear();
}