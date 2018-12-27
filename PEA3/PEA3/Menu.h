#pragma once
#include "Graph.h"
#include <vector>
#include "EvolutionAlgorithm.h"


class Menu
{
	Graph graph; //Obiekt klasy Menu bêdzie zawiera³ atrybut klasy Graf, który jest po prostu przedstawieniem grafu w postaci macierzy s¹siedztwa
	EvolutionAlgorithm evolution;
	int stop;
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g³ówne programu
	void displayHamilton(int cost, std::vector<int> path);
	void fileChoice();
	void autoStopSetting();
	void mutationSetting();
	void crossingSetting();
	void startPopulationSetting();
	void mutationMethodChoice();
};

