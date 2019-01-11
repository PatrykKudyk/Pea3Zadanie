#pragma once
#include "Graph.h"
#include <vector>
#include "TimeMeasure.h"

struct populationMember	//struktura symbolizuj�ca osobnika populacji
{
	int cost;		//koszt przej�cia
	std::vector<int> path;	//droga
};

class EvolutionAlgorithm
{
	Graph graph;		//graf oraz jego wielkosc (czyli liczba wierzcholkow)
	std::vector<int> path;	//vector, kt�ry przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt
	TimeMeasure timer;	//licznik odpowiedzialny za liczenie czasu jaki up�yn�� - U�ywam w�asnej klasy TimeMeassure
	float mutation;		//wsp�czynnik mutacji
	int startPopulationSize;	//wielko�� populacji startowej
	float crossing;		//wspolczynnik krzyzowania
	int stop;		//czas, po ktorym algorytm ma si� zako�czy�
	int mutationMethod; //metoda mutacji.  1 lub 2. Startowa to 1;
public:
	EvolutionAlgorithm();	//konstruktor
	~EvolutionAlgorithm();	//destruktor
	bool whileCheck();		//metoda sprawdzaj�ca, czy czas zosta� przekroczony
	void simulatingEvolution();		//g��wna metoda klasy odpowiadaj�ca za przeprowadzenie symulacji
	populationMember generateCrossing(populationMember firstMember, populationMember secondMember);	//metoda generuj�ca dziecko b�d�ce wynikiem krzy�owania dwojga rodzic�w podanych jako parametry metody
	populationMember generateMutationFirstMethod(populationMember member);	//metoda przeprowadzaj�ca pierwszy rodzaj mutacji (SWAP) na osobniku podanym jako parametr metody
	populationMember generateMutationSecondMethod(populationMember member);	//metoda przeprowadzaj�ca drugi rodzaj mutacji (SCRAMBLE) na osobniku podanym jako parametr metody
	int calculatePathCost(std::vector<int> permutation);	//metoda obliczaj�ca koszt przej�cia po drodze podawanej jako parametr metody
	std::vector<populationMember> generatingStartPopulation();	//metoda generuj�ca populacj� pocz�tkow�
	std::vector<int> generatingPermutation();	//metoda generuj�ca losow� permutacj� wierzcho�k�w grafu
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

