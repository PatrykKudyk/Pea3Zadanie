#pragma once
#include <xstring>

class Graph
{
	int vertices; // ilosc wierzcholkow grafu
	long **graph; //wskaŸnik na tablice wskaŸników
public:
	Graph();
	~Graph();
	void createGiven(std::string name, int numberOfVerts);	//tworzê graf przy u¿yciu pliku o zadanej nazwie oraz (dla u³atwienia) liczbie wierzcho³ków
	void createGiven(std::string name);		//tworzê graf przy u¿yciu pliku o zadanej nazwie
	void clear();		//czyszczenie grafu
	void graphReset();	//reset grafu
	void display();		//wyœwietlenie grafu
	int getVertices(); //pobiera ilosc wierzcholkow
	void setVertices(int value);
	long** getGraph();
	void setGraphFrag(Graph &obj);
};

