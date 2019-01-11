#pragma once
#include "Graph.h"
#include <vector>
#include "EvolutionAlgorithm.h"


class Menu
{
	Graph graph; //Obiekt klasy Menu b�dzie zawiera� atrybut klasy Graf, kt�ry jest po prostu przedstawieniem grafu w postaci macierzy s�siedztwa
	EvolutionAlgorithm evolution;	//atrybut klasy obs�uguj�cej algorytm ewolucji
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g��wne programu
	void displayHamilton(int cost, std::vector<int> path);	//wy�wietlenie wynik�w
	void fileChoice();	//wyb�r pliku do wczytania
	void autoStopSetting();	//ustawienie czasu, po kt�rym ma nast�pi� stop
	void mutationSetting();	//ustawienie wspolczynnika mutacji
	void crossingSetting();	//ustawienie wspolczynnika krzy�owania
	void startPopulationSetting();	//ustawienie wielko�ci populacji startowej
	void mutationMethodChoice();	//wyb�r metody mutacji
};

