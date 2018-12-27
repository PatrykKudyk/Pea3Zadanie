#pragma once
#include "Graph.h"
#include <vector>
#include "TimeMeasure.h"

class AnnealingSimulation
{
	Graph graph;		//graf oraz jego wielkosc (czyli liczba wierzcholkow)
	std::vector<int> path;	//vector, który przechowuje kolejne wierzcholki po ktorych przechodzi algorytm
	int pathCost;	//zmienna, ktora przechowuje najnizszy koszt
	float coolingCoefficient;
	TimeMeasure timer;
	int stop;
	double timeBest;
	bool stopActivated;
	float tempEnd;
	float tempStart;
public:
	AnnealingSimulation();
	~AnnealingSimulation();
	bool whileCheck(float temperature);
	void simulation();
	std::vector<int> getPermutation();
	std::vector<int> generateNeighbour(std::vector<int> permutation);
	int calculatePathCost(std::vector<int> permutation);
	float propability(float temperature, int cost1, int cost2);
	std::vector<int> getPath();
	void setPath(std::vector<int> gPath);
	int getPathCost();
	void setPathCost(int gPathCost);
	Graph getGraph();
	void setGraph(Graph &givenGraph);	
	float getCoolingCoefficient();
	void setCoolingCoefficient(float data);
	int getStop();
	void setStop(int data);
	double getTimeBest();
	bool getStopActivated();
	float getTempEnd();
	float getTempStart();
	void setTempStart(float data);
};

