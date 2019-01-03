#include "EvolutionAlgorithm.h"
#include <algorithm>


EvolutionAlgorithm::EvolutionAlgorithm()
{
	stop = 100;
	mutationMethod = 1;
}

EvolutionAlgorithm::~EvolutionAlgorithm()
{
}

bool compareByWeight(const populationMember &a, const populationMember &b)
{
	return a.cost < b.cost;
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
		int end = startPopulation.size();
		for (int i = 0; i < end; i++)
		{
			if ((rand() % 1000) / 1000.0 < crossing)
			{
				int a, b;
				do
				{
					a = rand() % startPopulation.size();
					b = rand() % startPopulation.size();
				} while (a == b);
				startPopulation.push_back(generateCrossing(startPopulation[a], startPopulation[b]));
			}
		}
		int c;
		for (int i = 0; i < startPopulation.size(); i++)
			if ((rand() % 1000) / 1000.0 < mutation)
				switch (mutationMethod)
				{
				case 1:
					c = rand() % startPopulation.size();
					startPopulation[c] = generateMutationFirstMethod(startPopulation[c]);
					break;
				case 2:
					if (graph.getVertices() > 10)
					{
						c = rand() % startPopulation.size();
						startPopulation[c] = generateMutationSecondMethod(startPopulation[c]);
					}
					break;
				default:
					break;
				}

		sort(startPopulation.begin(), startPopulation.end(), compareByWeight);

		while (startPopulation.size() > startPopulationSize)
		{
			startPopulation.pop_back();
		}
	} while (whileCheck());

	path = startPopulation.begin()->path;
	pathCost = startPopulation.begin()->cost;
}

populationMember EvolutionAlgorithm::generateCrossing(populationMember firstMember, populationMember secondMember)
{
	std::vector<int> crossedMember;
	int halfSize = graph.getVertices() / 2;
	bool *visited = new bool[graph.getVertices()];
	for (int i = 0; i < graph.getVertices(); i++)
		visited[i] = false;
	for (int i = 0; i < halfSize; i++)
	{
		crossedMember.push_back(firstMember.path[i]);
		visited[crossedMember[i]] = true;
	}
	for (int i = 0; i < secondMember.path.size(); i++)
	{
		if (!visited[secondMember.path[i]])
			crossedMember.push_back(secondMember.path[i]);
	}
	delete[] visited;
	populationMember temp;
	temp.path = crossedMember;
	temp.cost = calculatePathCost(temp.path);
	return temp;
}

populationMember EvolutionAlgorithm::generateMutationFirstMethod(populationMember member)
{
	int a, b;
	do
	{
		a = rand() % graph.getVertices();
		b = rand() % graph.getVertices();
	} while (a == b);
	std::swap(member.path[a], member.path[b]);
	member.cost = calculatePathCost(member.path);
	return member;
}

populationMember EvolutionAlgorithm::generateMutationSecondMethod(populationMember member)
{
	int a = rand() % (graph.getVertices() - 7);
	std::vector<int> mutation;
	for (int i = a; i < a + 6; i++)
		mutation.push_back(member.path[i]);
	random_shuffle(mutation.begin(), mutation.end());
	for (int i = a, j = 0; i < a + 6; i++, j++)
		member.path[i] = mutation[j];
	member.cost = calculatePathCost(member.path);
	return member;
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
