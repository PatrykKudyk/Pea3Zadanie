#pragma once
#include <xstring>

class Graph
{
	int vertices; // ilosc wierzcholkow grafu
	long **graph; //wska�nik na tablice wska�nik�w
public:
	Graph();
	~Graph();
	void createGiven(std::string name, int numberOfVerts);
	void createGiven(std::string name);
	void clear();
	void graphReset();
	void display();
	int getVertices(); //pobiera ilosc wierzcholkow
	void setVertices(int value);
	long** getGraph();
	void setGraphFrag(Graph &obj);
};

