#include "EvolutionAlgorithm.h"
#include <algorithm>


EvolutionAlgorithm::EvolutionAlgorithm()
{
	stop = 200;
	mutationMethod = 1;
}

EvolutionAlgorithm::~EvolutionAlgorithm()
{
}

bool EvolutionAlgorithm::whileCheck()
{
	double time = timer.getCounter();
	if (time >= static_cast<double>(stop))
		return false;
	
	return true;
}

void EvolutionAlgorithm::simulatingEvolution()
{
	timer.startCounting();
	std::vector<populationMember> startPopulation = generatingStartPopulation();
	do
	{
		for(int i = 0; i < crossing*startPopulationSize; i++)
		{
			
		}
	} while (whileCheck());

	path = permutation;
	pathCost = minimalCost;
}

int EvolutionAlgorithm::calculatePathCost(std::vector<int> permutation)
{
	int cost = 0;
	for (int i = 0; i < permutation.size() - 1; i++)
	{
		int currentVert = permutation.at(i);
		int nextVert = permutation.at(i + 1);
		cost += graph.getGraph()[currentVert][nextVert];
	}
	cost += graph.getGraph()[permutation[graph.getVertices() - 1]][permutation[0]];
	return cost;
}

std::vector<populationMember> EvolutionAlgorithm::generatingStartPopulation()
{
	std::vector<populationMember> startPopulation;
	for (int i = 0; i < startPopulationSize; i++)
	{
		populationMember temp;
		temp.path = generatingPermutation();
		temp.cost = calculatePathCost(temp.path);
		startPopulation.push_back(temp);
	}
	return startPopulation;
}

std::vector<int> EvolutionAlgorithm::generatingPermutation()
{
	std::vector<int> permutation;
	for (int i = 0; i < graph.getVertices(); i++)
		permutation.push_back(i);
	random_shuffle(permutation.begin(), permutation.end());
	return permutation;
}

std::vector<int> EvolutionAlgorithm::getPath()
{
	return path;
}

void EvolutionAlgorithm::setPath(std::vector<int> gPath)
{
	path = gPath;
}

int EvolutionAlgorithm::getPathCost()
{
	return pathCost;
}

void EvolutionAlgorithm::setPathCost(int gPathCost)
{
	pathCost = gPathCost;
}

Graph EvolutionAlgorithm::getGraph()
{
	return graph;
}

void EvolutionAlgorithm::setGraph(Graph& givenGraph)
{
	graph.setVertices(givenGraph.getVertices());
	graph.setGraphFrag(givenGraph);
}

int EvolutionAlgorithm::getStop()
{
	return stop;
}

void EvolutionAlgorithm::setStop(int data)
{
	stop = data;
}

float EvolutionAlgorithm::getMutation()
{
	return mutation;
}

void EvolutionAlgorithm::setMutation(float data)
{
	mutation = data;
}

int EvolutionAlgorithm::getStartPopulation()
{
	return startPopulationSize;
}

void EvolutionAlgorithm::setStartPopulation(int data)
{
	startPopulationSize = data;
}

float EvolutionAlgorithm::getCrossing()
{
	return crossing;
}

void EvolutionAlgorithm::setCrossing(float data)
{
	crossing = data;
}

int EvolutionAlgorithm::getMutationMethod()
{
	return mutationMethod;
}

void EvolutionAlgorithm::setMutationMethod(int data)
{
	mutationMethod = data;
}
