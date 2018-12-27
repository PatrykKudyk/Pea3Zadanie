#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include "AnnealingSimulation.h"


using namespace std;


Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::mainMenu()
{
	bool progWork = true;	//zmienna logiczna, ktora odpowiada za dzialanie badz wylaczenie programu
	int choise;	//numer, ktory wprowadza uzytkownik w momencie wyboru
	do {
		system("cls");
		cout << "[1] Wczytaj dane z pliku." << endl
			<< "[2] Wprowadz kryterium stopu." << endl
			<< "[3] Wybor sasiedztwa dla TS." << endl
			<< "[4] Uruchomienie algorytmu TS." << endl
			<< "[5] Ustawienie wspolczynnika zmiany temperatury dla SW." << endl
			<< "[6] Uruchomienie algorytmu SW." << endl
			<< "[7] Wyjscie z programu" << endl;
		cin >> choise;
		switch (choise)
		{
		case 1:
			system("cls");
			fileChoice();
			break;
		case 2:
			system("cls");
			autoStopSetting();
			break;
		case 3:
			system("cls");
			
			break;
		case 4:
			system("cls");
			if (graph.getVertices() != 0)
			{

			}
			else
			{
				cout << "Graf jest pusty, nie mozna przeprowadzic wybranej oepracji!" << endl;
				cin.get();
				cin.get();
			}
			break;
		case 5:
			coefficientSetting();
			break;
		case 6:
			system("cls");
			annealing.setGraph(graph);
			if (graph.getVertices() != 0)
				if (annealing.getCoolingCoefficient() != NULL)
				{
					annealing.simulation();
					displayHamilton(annealing.getPathCost(), annealing.getPath());
					cin.get();
					cin.get();
				}
				else
				{
					cout << "Wspolczynnik zmiany temperatury nie zostal podany! Podaj go i dopiero uruchom algorytm." << endl;
					cin.get();
					cin.get();
				}
			else
			{
				cout << "Graf jest pusty, nie mozna przeprowadzic wybranej oepracji!" << endl;
				cin.get();
				cin.get();
			}
			break;
		case 7:
			progWork = false;
			break;
		default:
			break;
		}
	} while (progWork);
}

string Menu::getFileName()
{
	string name;	//tworzy zmienna klasy string
	cout << "Podaj nazwe pliku : ";
	cin >> name;	//pobiera nazwe od uzytkownika
	name = name + ".txt"; //zmieniam nazwe pliku na taka obslugiwana przez program
	return name;	//zwraca podana przez uzytkownika nazwe
}

int Menu::getNumber()
{
	int choise;
	cout << "Z ktorego wierzcholka chcesz wyruszyc?" << endl
		<< "[1] Z wybranego." << endl
		<< "[2] Z losowego." << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		return getNumber(graph.getVertices());
	case 2:
		return (rand() % graph.getVertices());
	default:
		break;
	}
	return 0;
}

int Menu::getNumber(int vert)
{
	int number;
	cout << endl << "Podaj wierzcholek startowy z zakresu: [0, " << vert - 1 << "]" << endl;
	cin >> number;
	return number;
}

void Menu::displayHamilton(int cost, vector<int> path)
{
	if (graph.getVertices() != 0)	//sprawdzenie czy graf nie jest pusty
	{
		cout << "Minimalny cykl hamiltona dla grafu to :" << endl;
		for (int i = 0; i < path.size(); i++)
		{
			if (i != 0)
				cout << " - ";
			cout << path[i];	//wypisanie kolejnych wierzcholkow przejscia
		}
		cout << " - " <<  path[0];
		cout << endl << endl << "Waga tego cyklu to : " << cost << endl;	//wyswietlenie kosztu najtanszego przejscia
		if (annealing.getStopActivated())
			cout << "Jest to najlepszy wynik znaleziony po uplywie " << annealing.getStop() << " s" << endl << "Odnaleziono go po uplywie " << annealing.getTimeBest() << " s." << endl;
		else
			cout << "Wynik ten zostal odszukany przed uplywem wyznaczonego czasu, a dokladniej po czasie " << annealing.getTimeBest() << " s." << endl;
		cout << "Poczatkowa temperatura wynosila: " << annealing.getTempStart() << endl
			<< "Koncowa zas wyniosla: " << annealing.getTempEnd() << endl;
	}
	else
		cout << "Graf nie posiada wierzcholkow! Nie posiada tez cyklu hamiltona.";
}

void Menu::fileChoice()
{
	int choise;
	cout << "Jaki plik chcialbys otworzyc?" << endl
		<< "[1] ftv47.atsp" << endl
		<< "[2] ftv170.atsp" << endl
		<< "[3] rbg403.atsp" << endl
		<< "[4] tsp_15.txt" << endl;
	cin >> choise;
	switch (choise)
	{
	case 1:
		graph.createGiven("ftv47.atsp", 48);
		break;
	case 2:
		graph.createGiven("ftv170.atsp", 171);
		break;
	case 3:
		graph.createGiven("rbg403.atsp", 403);
		break;
	case 4:
		graph.createGiven("tsp_15.txt");
		break;
	default:
		break;
	}
}

void Menu::coefficientSetting()
{
	float number;
	cout << "Jaki wspolczynnik zmiany temperatury chcialbys ustawic?" << endl;
	cin >> number;
	annealing.setCoolingCoefficient(number);
}

void Menu::autoStopSetting()
{
	int number;
	cout << "Po jakim czasie chcialbys automatycznie przerwac algorytm?" << endl
		<< "Czas podaj w sekundach." << endl;
	cin >> number;
	annealing.setStop(number);
}