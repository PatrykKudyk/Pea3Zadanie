#pragma once
#include "Graph.h"
#include <vector>
#include "AnnealingSimulation.h"


class Menu
{
	Graph graph; //Obiekt klasy Menu b�dzie zawiera� atrybut klasy Graf, kt�ry jest po prostu przedstawieniem grafu w postaci macierzy s�siedztwa
	AnnealingSimulation annealing;
	int stop;
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g��wne programu
	std::string getFileName();
	int getNumber();
	int getNumber(int vert); // pobiera numer, przeciazenie
	void displayHamilton(int cost, std::vector<int> path);
	void fileChoice();
	void coefficientSetting();
	void autoStopSetting();
};

