#pragma once
#include "Graph.h"
#include <vector>
#include "EvolutionAlgorithm.h"


class Menu
{
	Graph graph; //Obiekt klasy Menu b�dzie zawiera� atrybut klasy Graf, kt�ry jest po prostu przedstawieniem grafu w postaci macierzy s�siedztwa
	EvolutionAlgorithm evolution;
	int stop;
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g��wne programu
	void displayHamilton(int cost, std::vector<int> path);
	void fileChoice();
	void autoStopSetting();
	void mutationSetting();
	void crossingSetting();
	void startPopulationSetting();
	void mutationMethodChoice();
};

