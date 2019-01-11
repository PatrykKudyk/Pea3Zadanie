#pragma once
#include <xstring>

class Graph
{
	int vertices; // ilosc wierzcholkow grafu
	long **graph; //wska�nik na tablice wska�nik�w
public:
	Graph();
	~Graph();
	void createGiven(std::string name, int numberOfVerts);	//tworz� graf przy u�yciu pliku o zadanej nazwie oraz (dla u�atwienia) liczbie wierzcho�k�w
	void createGiven(std::string name);		//tworz� graf przy u�yciu pliku o zadanej nazwie
	void clear();		//czyszczenie grafu
	void graphReset();	//reset grafu
	void display();		//wy�wietlenie grafu
	int getVertices(); //pobiera ilosc wierzcholkow
	void setVertices(int value);
	long** getGraph();
	void setGraphFrag(Graph &obj);
};

