#include "AnnealingSimulation.h"
#include <algorithm>
#include <iostream>


AnnealingSimulation::AnnealingSimulation()
{
	stop = 200;
}

AnnealingSimulation::~AnnealingSimulation()
{
}

bool AnnealingSimulation::whileCheck(float temperature)
{
	double time = timer.getCounter();
	if (time >= static_cast<double>(stop))
	{
		//std::cout << "Czas minal" << std::endl;
		stopActivated = true;
		return false;
	}

	if (temperature >= 0.01)
		return true;

	//std::cout << "Temperatura za niska" << std::endl;
	return false;
}

void AnnealingSimulation::simulation()
{
	stopActivated = false;
	timer.startCounting();
	std::vector<int> permutation = getPermutation();	//inicjalizacja losowej œcie¿ki pocz¹tkowej jako wektora intów
//	int step = 0;		//inicjalizacja licznika kroków - pocz¹tkowo 0
	std::vector<int> bestPath = permutation;
	int minimalCost = calculatePathCost(permutation);
	float temperature = minimalCost / 1.618;			//obliczenie temperatury startowej
	tempStart = temperature;
	//float temperature = tempStart;
	do
	{
		
		for(int i = 0; i < graph.getVertices(); i++)
		{
			std::vector<int> neighbour = generateNeighbour(permutation);
			int currentCost = calculatePathCost(neighbour);
			if (currentCost <= minimalCost)
			{
				permutation = neighbour;
				minimalCost = currentCost;
				timeBest = timer.getCounter();
				tempEnd = temperature;
			}
			else if(propability(temperature,minimalCost,currentCost) < (rand()%1000 / 1000.0))
			{
				permutation = neighbour;
				minimalCost = currentCost;
				timeBest = timer.getCounter();
				tempEnd = temperature;
			}
		}
		temperature = temperature*coolingCoefficient;
		//	step++;
	} while (whileCheck(temperature));
	//std::cout << step*1618*graph.getVertices() << std::endl;
	//std::cin.get();
	path = permutation;
	pathCost = minimalCost;
}

std::vector<int> AnnealingSimulation::getPermutation()
{
	/*std::vector<int> permutation;	//tworze wektor intów
	for (int i = 0; i < graph.getVertices(); i++)	
		permutation.push_back(i);					//dodaje wszystkie wierzcholki grafu do wektora
	std::random_shuffle(permutation.begin(), permutation.end());	//mieszam wszystkie wierzcho³ki*/
	
	bool loopOn = true;

	bool *visited = new bool[graph.getVertices()];
	for (int i = 0; i < graph.getVertices(); i++)
		visited[i] = false;

	int startVert = rand() % graph.getVertices();
	visited[startVert] = true; 

	std::vector<int> permutation;
	permutation.push_back(startVert);

	std::vector<int> vectors;
	int index;
	do
	{
		vectors.clear();	//usuwam z wektora wszystkie struktury
		for (int i = 0; i < graph.getVertices(); i++)	//iteruje po wszystkich wierzcho³kach
			if (visited[i] == false)		//sprawdzam, czy wierzcholek byl juz odwiedzony wczesniej
				vectors.push_back(i);	//dodaje strukture do wektora
			
		//-------ZNALEZIENIE NAJMNIEJSZEGO-------//
		int minRed = LONG_MAX;	//ustawiam minimalna redukcje na nieskonczonosc
		index = NULL;		//zeruje index
		for (int i = 0; i < vectors.size(); i++)		//iteruje po wszystkich wierzcholkach
			if(startVert != vectors[i])
				if (graph.getGraph()[startVert][vectors[i]] < minRed)		//sprawdzam czy redukcja chwilowej struktury jest mniejsza niz aktualna najmniejsza 
				{
					index = vectors[i];		//zapamietuje index tejze struktury w wektorze
					minRed = graph.getGraph()[startVert][vectors[i]];	//aktualizuje najmniejsza redukcjê
				}
		//---------------------------------------//

		startVert = index;
		visited[index] = true;
		permutation.push_back(index);				//aktualizuje chwilow¹ œcie¿kê hamiltona, dla chwilowego kosztu
		loopOn = false;
		for (int i = 0; i < graph.getVertices(); i++)
			if (visited[i] == false)
				loopOn = true;
	} while (loopOn);		//pêtla dziz³a dopóki nie zostanie znaleziona œcie¿ka
	delete[] visited;
	return permutation;		//zwracam wektor z losowo pomieszanymi wierzcho³kami
}

std::vector<int> AnnealingSimulation::generateNeighbour(std::vector<int> permutation)
{
	std::vector<int> neighbour = permutation;
	int a, b;
	do
	{
		a = rand() % graph.getVertices();
		b = rand() % graph.getVertices();
	} while (a == b);
	std::swap(neighbour.at(a), neighbour.at(b));
	return neighbour;
}

int AnnealingSimulation::calculatePathCost(std::vector<int> permutation)
{
	int cost = 0;
	for(int i = 0; i < permutation.size() - 1; i++)
	{
		int currentVert = permutation.at(i);
		int nextVert = permutation.at(i + 1);
		cost += graph.getGraph()[currentVert][nextVert];
	}
	cost += graph.getGraph()[permutation[graph.getVertices() - 1]][permutation[0]];
	return cost;
}

float AnnealingSimulation::propability(float temperature, int cost1, int cost2)
{
	return exp(-1*(float)(cost1 - cost2) / temperature);
}

std::vector<int> AnnealingSimulation::getPath()
{
	return path;
}

void AnnealingSimulation::setPath(std::vector<int> gPath)
{
	path = gPath;
}

int AnnealingSimulation::getPathCost()
{
	return pathCost;
}

void AnnealingSimulation::setPathCost(int gPathCost)
{
	pathCost = gPathCost;
}

Graph AnnealingSimulation::getGraph()
{
	return graph;
}

void AnnealingSimulation::setGraph(Graph& givenGraph)
{
	graph.setVertices(givenGraph.getVertices());
	graph.setGraphFrag(givenGraph);
}

float AnnealingSimulation::getCoolingCoefficient()
{
	return coolingCoefficient;
}

void AnnealingSimulation::setCoolingCoefficient(float data)
{
	coolingCoefficient = data;
}

int AnnealingSimulation::getStop()
{
	return stop;
}

void AnnealingSimulation::setStop(int data)
{
	stop = data;
}

double AnnealingSimulation::getTimeBest()
{
	return timeBest;
}

bool AnnealingSimulation::getStopActivated()
{
	return stopActivated;
}

float AnnealingSimulation::getTempEnd()
{
	return tempEnd;
}

float AnnealingSimulation::getTempStart()
{
	return tempStart;
}

void AnnealingSimulation::setTempStart(float data)
{
	tempStart = data;
}
