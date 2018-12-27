#pragma once
#include "Graph.h"
#include <vector>
#include "AnnealingSimulation.h"


class Menu
{
	Graph graph; //Obiekt klasy Menu bêdzie zawiera³ atrybut klasy Graf, który jest po prostu przedstawieniem grafu w postaci macierzy s¹siedztwa
	AnnealingSimulation annealing;
	int stop;
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g³ówne programu
	std::string getFileName();
	int getNumber();
	int getNumber(int vert); // pobiera numer, przeciazenie
	void displayHamilton(int cost, std::vector<int> path);
	void fileChoice();
	void coefficientSetting();
	void autoStopSetting();
};

