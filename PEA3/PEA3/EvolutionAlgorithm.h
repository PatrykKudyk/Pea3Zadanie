#pragma once
#include "Graph.h"
#include <vector>
#include "TimeMeasure.h"

struct populationMember
{
	int cost;
	std::vector<int> path;
};

class EvolutionAlgorithm
{
	Graph graph;		//graf oraz jego wielkosc (czyli liczba wierzcholkow)
	std::vector<int> path;	//vector, który przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt
	TimeMeasure timer;
	float mutation;
	int startPopulationSize;
	float crossing;
	int stop;
	int mutationMethod; //metoda mutacji.  1 lub 2. Startowa to 1;
public:
	EvolutionAlgorithm();
	~EvolutionAlgorithm();
	bool whileCheck();
	void simulatingEvolution();
	int calculatePathCost(std::vector<int> permutation);
	std::vector<populationMember> generatingStartPopulation();
	std::vector<int> generatingPermutation();
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

