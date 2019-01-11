#include "Graph.h"
#include <iostream>
#include <fstream> //biblioteka do "obs�ugi" plik�w
#include <string>
#include <sstream>

using namespace std;

Graph::Graph()
{
	vertices = 0;
}

Graph::~Graph()
{
	clear();
}

void Graph::createGiven(string name, int numberOfVerts)
{
	ifstream plik; //tworze plik
	int counter = 0; // inicjuje licznik, kt�ry u�atwi wpisywanie danych (b�dzie liczy� wiersze)
	plik.open(name, ios::in); //otwieram plik
	if (plik.good() == true)	//sprawdzam, czy plik otworzyl sie poprawnie
	{
		graphReset(); //resetuje graf
		vertices = numberOfVerts;	//ustawienie wielko�ci grafu na podan� jako parametr
		graph = new long *[vertices];	//tworze tablice wskaznikow, ktorej wielkosc jest rowna ilosci wierzcholkow
		for (int i = 0; i < vertices; i++)	//tworze wiersze w tablicy wskaznikow, wiersze dlugosci odpowiadajacej ilosci wierzcholkow
			graph[i] = new long[vertices];

		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				graph[i][j] = 0;		//przypisuje wszystkim komorkom wartosc poczatkowa 0
		string word;		//inicjalizacja stringa do odczytywania danych
		while (true)	//p�tla niesko�czona (w p�tli jest warunek wyj�cia)
		{
			plik >> word;	//odczytanie fragmentu pliku
			if (word == "EDGE_WEIGHT_SECTION")	//sprawdzenie czy w pliku rozpocz�o si� podawanie wierzcho�k�w
			{
				while (word != "EOF") {	//p�tla odczytuj�ca wierzcho�ki tak d�ugo jak s� podawane
					for (int i = 0; i < vertices; i++)
					{
						plik >> word;	//odczytanie fragmentu pliku
						if (word != "EOF")	//sprawdzenie, czy nie jest to "EOF" - wyst�puje na ko�cu pliku
						{
							istringstream iss(word);	//konwersja string na inta
							iss >> graph[counter][i];	//przypisanie warto�ci odczytanej do odpowiedniej kom�rki tablicy
							if (counter == i)
								graph[counter][i] = 100000000;	//ustawienie warto�ci 100000000 na przek�tnej macierzy (tablicy)
						}
					}
					counter++;	//zwi�kszam numer wiersza
				}
				break;
			}
		}
	}
	else
	{
		system("cls");
		cout << "Nie udalo sie otworzyc pliku." << endl;
		cin.get();
		cin.get();
		graphReset(); //resetuje graf
	}
	plik.close();	 // zamykam plik
}

void Graph::createGiven(std::string name)
{
	ifstream plik; //tworze plik
	int counter = 0; // inicjuje licznik, kt�ry u�atwi wpisywanie danych (b�dzie liczy� wiersze)
	plik.open(name, ios::in); //otwieram plik
	if (plik.good() == true)	//sprawdzam, czy plik otworzyl sie poprawnie
	{
		graphReset(); //resetuje graf
		plik >> vertices;
		graph = new long int *[vertices];	//tworze tablice wskaznikow, ktorej wielkosc jest rowna ilosci wierzcholkow
		for (int i = 0; i < vertices; i++)	//tworze wiersze w tablicy wskaznikow, wiersze dlugosci odpowiadajacej ilosci wierzcholkow
			graph[i] = new long int[vertices];

		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
				graph[i][j] = 0;		//przypisuje wszystkim komorkom wartosc poczatkowa 0

		while (!plik.eof())
		{
			for (int i = 0; i < vertices; i++)
				plik >> graph[counter][i];	// w p�tli przypisuje warto�ci po kolei do wiersza oznaczonego jako "counter"

			counter++;	//zwi�kszam numer wiersza
			if (counter >= vertices)  //warunek przekroczenia ilosci danych, jesli plik z danymi by�by �le podany
				break;
		}
	}
	else
	{
		system("cls");
		cout << "Nie udalo sie otworzyc pliku." << endl;
		cin.get();
		cin.get();
		graphReset(); //resetuje graf
	}
	plik.close();	 // zamykam plik
}

void Graph::clear()
{
	for (int i = 0; i < vertices; i++)
		delete[] graph[i];
	delete[] graph;
}

void Graph::graphReset()
{
	if (vertices != 0) //sprawdzam, czy istnieje ju� jaki� graf. Je�li tak to go usuwam i dopiero wczytuje nowy
	{
		clear(); //czyszczenie grafu
		long **temp1 = nullptr; // tworze wskaznik na nowy graf
		graph = temp1; //przypisuje wskaznik 
		vertices = 0; //zeruje liczbe wierzcholkow
	}
}

void Graph::display()
{
	if (vertices > 0) {
		cout << "Wczytany graf posiada " << vertices << " wierzcholkow, a jego reprezentacja jest nastepujaca:" << endl << endl;

		for (int i = 0; i < vertices; i++)
		{
			if (i == 0)
			{
				cout << "\t";
				for (int m = 0; m < vertices; m++)
					cout << m << "\t";	//wypisuje numery wierzcholkow w pierwszym wierszu
				cout << "<--- numery wierzcholkow" << endl;
				for (int ilosc = 0; ilosc < (vertices * 8) + 2; ilosc++)	//wypisanie wiersza skladajacego sie z ciagu: "----(...)--"
					cout << "-";
				cout << endl;
			}
			cout << i << "\t"; // wypisanie numeru wiersza w pierwszej kolumnie
			for (int j = 0; j < vertices; j++)
				cout << this->graph[i][j] << "\t";					//wypisywanie wartosci z macierzy

			cout << endl;
			if (i % 2 == 1)
				for (int ilosc = 0; ilosc < (vertices * 8) + 2; ilosc++)		//co drugi wiersz oddzielony jest ciagiem: "----(...)--"
					cout << "-";
			else
				for (int ilosc = 0; ilosc < (vertices * 8) + 2; ilosc++)	//co drugi wiersz oddzielony jest ciagiem: "~~~~(...)~~"
					cout << "~";
			cout << endl;
		}
		cout << "^\n|\n|\nwierzcholki" << endl;
	}
	else
		cout << "Graf nie posiada wierzcholkow, wiec nie mozna go wyswietlic." << endl;
}

int Graph::getVertices()
{
	return vertices;
}

void Graph::setVertices(int value)
{
	vertices = value;
}

long** Graph::getGraph()
{
	return graph;
}

void Graph::setGraphFrag(Graph &obj)
{
	graph = new long*[obj.vertices];
	for (int i = 0; i < obj.vertices; i++)
		graph[i] = new long[obj.vertices];

	for (int i = 0; i < obj.vertices; i++)
		for (int j = 0; j < obj.vertices; j++)
			graph[i][j] = obj.graph[i][j];

}
