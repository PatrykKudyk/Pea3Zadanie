#pragma once
#include "Graph.h"
#include <vector>
#include "TimeMeasure.h"

struct populationMember	//struktura symbolizuj¹ca osobnika populacji
{
	int cost;		//koszt przejœcia
	std::vector<int> path;	//droga
};

class EvolutionAlgorithm
{
	Graph graph;		//graf oraz jego wielkosc (czyli liczba wierzcholkow)
	std::vector<int> path;	//vector, który przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt
	TimeMeasure timer;	//licznik odpowiedzialny za liczenie czasu jaki up³yn¹³ - U¿ywam w³asnej klasy TimeMeassure
	float mutation;		//wspó³czynnik mutacji
	int startPopulationSize;	//wielkoœæ populacji startowej
	float crossing;		//wspolczynnik krzyzowania
	int stop;		//czas, po ktorym algorytm ma siê zakoñczyæ
	int mutationMethod; //metoda mutacji.  1 lub 2. Startowa to 1;
public:
	EvolutionAlgorithm();	//konstruktor
	~EvolutionAlgorithm();	//destruktor
	bool whileCheck();		//metoda sprawdzaj¹ca, czy czas zosta³ przekroczony
	void simulatingEvolution();		//g³ówna metoda klasy odpowiadaj¹ca za przeprowadzenie symulacji
	populationMember generateCrossing(populationMember firstMember, populationMember secondMember);	//metoda generuj¹ca dziecko bêd¹ce wynikiem krzy¿owania dwojga rodziców podanych jako parametry metody
	populationMember generateMutationFirstMethod(populationMember member);	//metoda przeprowadzaj¹ca pierwszy rodzaj mutacji (SWAP) na osobniku podanym jako parametr metody
	populationMember generateMutationSecondMethod(populationMember member);	//metoda przeprowadzaj¹ca drugi rodzaj mutacji (SCRAMBLE) na osobniku podanym jako parametr metody
	int calculatePathCost(std::vector<int> permutation);	//metoda obliczaj¹ca koszt przejœcia po drodze podawanej jako parametr metody
	std::vector<populationMember> generatingStartPopulation();	//metoda generuj¹ca populacjê pocz¹tkow¹
	std::vector<int> generatingPermutation();	//metoda generuj¹ca losow¹ permutacjê wierzcho³ków grafu
	std::vector<int> getPath();
	void setPath(std::vector<int> gPath);
	int getPathCost();
	void setPathCost(int gPathCost);
	Graph getGraph();
	void setGraph(Graph &givenGraph);
	int getStop();
	void setStop(int data);
	float getMutation();
	void setMutation(float data);
	int getStartPopulation();
	void setStartPopulation(int data);
	float getCrossing();
	void setCrossing(float data);
	int getMutationMethod();
	void setMutationMethod(int data);
};

