#pragma once
#include "Graph.h"
#include <vector>
#include "EvolutionAlgorithm.h"


class Menu
{
	Graph graph; //Obiekt klasy Menu bêdzie zawiera³ atrybut klasy Graf, który jest po prostu przedstawieniem grafu w postaci macierzy s¹siedztwa
	EvolutionAlgorithm evolution;	//atrybut klasy obs³uguj¹cej algorytm ewolucji
public:
	Menu();
	~Menu();
	void mainMenu(); //menu g³ówne programu
	void displayHamilton(int cost, std::vector<int> path);	//wyœwietlenie wyników
	void fileChoice();	//wybór pliku do wczytania
	void autoStopSetting();	//ustawienie czasu, po którym ma nast¹piæ stop
	void mutationSetting();	//ustawienie wspolczynnika mutacji
	void crossingSetting();	//ustawienie wspolczynnika krzy¿owania
	void startPopulationSetting();	//ustawienie wielkoœci populacji startowej
	void mutationMethodChoice();	//wybór metody mutacji
};

