#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>


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
			<< "[2] Wprowadz kryterium stopu.\t[Aktualne]: " << evolution.getStop() << endl		//
			<< "[3] Ustawienie wielkosci populacji poczatkowej.\t[Aktualne]: " << evolution.getStartPopulation() << endl
			<< "[4] Ustawienie wspolczynnika mutacji.\t[Aktualne]: " << evolution.getMutation() << endl
			<< "[5] Ustawienie wspolczynnika krzyzowania.\t[Aktualne]: " << evolution.getCrossing() << endl
			<< "[6] Wybor metody mutacji.\t[Aktualne]: ";
		if (evolution.getMutationMethod() == 1)
			cout << "Swap";
		else
			cout << "Scrambling";
			cout << endl << "[7] Wykonanie algorytmu dla podanych parametrow." << endl
			<< "[8] Wyjscie z programu" << endl;
		cin >> choise;
		switch (choise)
		{
		case 1:
			system("cls");
			fileChoice();	//wywo³anie metody z wyborem pliku
			break;
		case 2:
			system("cls");
			autoStopSetting();	//wywo³anie metody z ustawianiem kryterium stopu
			break;
		case 3:
			system("cls");
			startPopulationSetting();	//wywo³anie metody z ustawianiem wielkoœci populacji startowej
			break;
		case 4:
			system("cls");
			mutationSetting();	//wywo³anie metody z wyborem metody mutacji
			break;
		case 5:
			system("cls");
			crossingSetting();	//wywo³anie metody z ustawianiem wspó³czynnika krzy¿owania
			break;
		case 6:
			system("cls");
			mutationMethodChoice();		//wywo³anie metody z ustawianiem wspó³czynnika mutacji
			break;
		case 7:
			system("cls");
			evolution.setGraph(graph);	//przypisanie wczytanego grafu do obiektu klasy odpowiedzialnej za przeprowadzenie Symulacji
			if (graph.getVertices() != 0)	//sprawdzenie, czy graf nie jest pusty
				if (evolution.getMutation() != NULL)	//sprawdzenie czy ustawiony zosta³ wspó³czynnik mutacji
				{
					if (evolution.getCrossing() != NULL)	//sprawdzenie czy ustawiony zosta³ wspó³czynnik krzy¿owania
					{
						if (evolution.getStartPopulation() != NULL)	//sprawdzenie czy ustawiona zosta³a wielkoœæ populacji startowej
						{
							evolution.simulatingEvolution();	//wywo³anie metody odpowiedzialnej za przeprowadzenie symulacji
							displayHamilton(evolution.getPathCost(), evolution.getPath());	//wyœwietlenie wyników symulacji
							cin.get();
							cin.get();
						}
						else
						{
							cout << "Wielkosc populacji poczatkowej nie zostala ustalona. Ustal ja i uruchom algorytm ponownie." << endl;
							cin.get();
							cin.get();
						}
					}
					else
					{
						cout << "Wspolczynnik krzyzowania nie zostal ustalony. Ustal go i uruchom algorytm ponownie." << endl;
						cin.get();
						cin.get();
					}
				}
				else
				{
					cout << "Wspolczynnik mutacji nie zostal ustalony. Ustal go i uruchom algorytm ponownie." << endl;
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
		case 8:
			progWork = false;
			break;
		default:
			break;
		}
	} while (progWork);
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
		<< "[3] rbg403.atsp" << endl;
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
	default:
		break;
	}
}

void Menu::autoStopSetting()
{
	int number;
	cout << "Po jakim czasie chcialbys automatycznie przerwac algorytm?" << endl
		<< "Czas podaj w sekundach." << endl;
	cin >> number;
	evolution.setStop(number);
}

void Menu::mutationSetting()
{
	float number;
	cout << "Jaki wspolczynnik mutacji chcialbys ustalic?" << endl;
	cin >> number;
	evolution.setMutation(number);
}

void Menu::crossingSetting()
{
	float number;
	cout << "Jaki wspolczynnik krzyzowania chcialbys ustalic?" << endl;
	cin >> number;
	evolution.setCrossing(number);
}

void Menu::startPopulationSetting()
{
	int number;
	cout << "Jaka ma byc wielkosc populacji startowej?" << endl;
	cin >> number;
	evolution.setStartPopulation(number);
}

void Menu::mutationMethodChoice()
{
	int number;
	cout << "Jaka metode mutacji chcialbys wybrac?" << endl
		<< "[1] - Pierwsza metoda - SWAP." << endl
		<< "[2] - Druga metoda - SCRAMBLE." << endl;
	cin >> number;
	evolution.setMutationMethod(number);
}
