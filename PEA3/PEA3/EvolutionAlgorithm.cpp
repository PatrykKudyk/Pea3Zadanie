#include "EvolutionAlgorithm.h"
#include <algorithm>


EvolutionAlgorithm::EvolutionAlgorithm()
{
	//ustawiam poczatkowe wartosci parametr�w aby mozna by�o szybciej przetestowa� program
	stop = 100;		//stop programu ustawiony na 100 sekund
	mutationMethod = 1;	//startowa metoda mutacji ustawiona na SWAP
	mutation = 0.01;	//wspolczynnik mutacji ustawiony domyslnie na 0.01
	startPopulationSize = 100;	//populacja startowa ustawiona na 100 osobnik�w
	crossing = 0.75;	//wspolczynnik krzyzowania ustawiony na 0.75
}

EvolutionAlgorithm::~EvolutionAlgorithm()
{
}

bool compareByWeight(const populationMember &a, const populationMember &b)		//komparator uzywany do sortowania wektora, porownuje wagi dwoch osobnikow
{
	return a.cost < b.cost;
}

bool EvolutionAlgorithm::whileCheck()	//metoda sprawdzajaca czy zostal przekroczony czas algorytmu
{
	double time = timer.getCounter();		//poranie aktualnego czasu jaki min�� od rozpocz�cia algorytmu
	if (time >= static_cast<double>(stop))	//sprawdzenie, czy czas jaki up�yn�� jest wi�kszy od czasu ustalonego jako max
		return false;		//po zwroceniu false algorytm zakonczy dzialanie

	return true;		//po zwroceniu true algorytm nadal b�dzie si� wykonywa�
}

void EvolutionAlgorithm::simulatingEvolution()		//glowna metoda klasy, kt�ra odpowiada za wykonanie symulacji
{
	timer.startCounting();		//wystartowanie licznika
	std::vector<populationMember> startPopulation = generatingStartPopulation();	//wygenerowanie populacji startowej przy pomocy metody generatingStartPopulation()
	do		//g��wna p�tla algorytmu
	{
		int end = startPopulation.size();	//ustawienie warunku zakonczenia p�tli for jako przekroczenie wielkosci populacji
		for (int i = 0; i < end; i++)	//p�tla odpowiedzialna za przeprowadzenie krzyzowa�
		{
			if ((rand() % 1000) / 1000.0 < crossing)	//warunek sprawdzaj�cy, czy wylosowana liczba jest mniejsza ni� wsp�czynnik krzy�owania
			{
				int a, b;		
				do
				{	//losowanie 2 osobnik�w z calo�ci populacji tak, aby by�y r�ne
					a = rand() % startPopulation.size();
					b = rand() % startPopulation.size();
				} while (a == b);
				startPopulation.push_back(generateCrossing(startPopulation[a], startPopulation[b]));	//dodanie nowego osobnika do populacji (dziecka) podaj�c do metody generateCrossing() dwa osobniki (rodzic�w)
			}
		}
		int c;
		for (int i = 0; i < startPopulation.size(); i++)	//p�tla odpowiadaj�ca za przeprowadzenie mutacji na populacji
			if ((rand() % 1000) / 1000.0 < mutation)	//warunek sprawdzaj�cy, czy wylosowana liczba jest mniejsza ni� wsp�czynnik mutacji
				switch (mutationMethod)		//sprawdzenie, kt�ra metoda mutacji zosta�a wybrana przez u�ytkownika
				{
				//metoda pierwsza - SWAP
				case 1:	
					c = rand() % startPopulation.size();	//wylosowanie osobnika z populacji
					startPopulation[c] = generateMutationFirstMethod(startPopulation[c]);	//zmutowanie wylosowanego wcze�niej osobnika przy pomocy metody generateMutationFirstMethod()
					break;
				
				//metoda druga - SCRAMBLE
				case 2: 
					if (graph.getVertices() > 10)	//warunek sprawdzaj�cy, czy graf posiada conajmniej 10 wierzcho�k�w - dodany, bo scrambling wycina ci�g 7 kolejnych wierzcho�k�w, a nie chcia�em, �eby wywali�o b��d
					{
						c = rand() % startPopulation.size();	//wylosowanie osobnika z populacji
						startPopulation[c] = generateMutationSecondMethod(startPopulation[c]);	//zmutowanie wylosowanego wcze�niej osobnika przy pomocy metody generateMutationSecondMethod()
					}
					break;
				default:
					break;
				}

		sort(startPopulation.begin(), startPopulation.end(), compareByWeight);	//posortowanie osobnik�w populacji wzgl�dem koszt�w dr�g - na pocz�tku znajduje si� najlepsze rozwi�zanie (najmniejszy koszt)


		while (startPopulation.size() > startPopulationSize)	//p�tla usuwaj�ca ko�cowe (najgorsze) drogi tak d�ugo, a� wielko�� populacji nie b�dzie r�wna pocz�tkowej
		{
			startPopulation.pop_back();		//usuni�cie ostatniego osobnika z wektora (populacji)
		}
	} while (whileCheck());	//sprawdzenie czy czas nie zosta� przekroczony


	path = startPopulation.begin()->path;		//zapami�tanie najlepszego osobnika z populacji jako atrybut�w path i pathCost (droga i jej koszt) w obiekcie
	pathCost = startPopulation.begin()->cost;	//
}

populationMember EvolutionAlgorithm::generateCrossing(populationMember firstMember, populationMember secondMember)	//metoda tworz�ca dziecko b�d�ce krzy��wk� dwojga rodzic�w podanych jako parametry metody
{
	std::vector<int> crossedMember;			//inicjalizacja genomu dziecka
	int halfSize = graph.getVertices() / 2;		//obliczenie tego jak wiele gen�w musi by� wyci�te z pierwszego rodzica tak, aby by�a to po�owa wszystkich
	bool *visited = new bool[graph.getVertices()];	//inicjalizacja dynamicznej tablicy wierzcho�k�w odwiedzonych
	for (int i = 0; i < graph.getVertices(); i++)
		visited[i] = false;			//wype�nienie ca�ej tablicy "false" - odpowiadaj�cemu nieodwiedzeniu
	for (int i = 0; i < halfSize; i++)		//p�tla wycinaj�ca pierwsz� po�ow� genomu Pierwszego Rodzica
	{
		crossedMember.push_back(firstMember.path[i]);	//dodawanie kolejnych gen�w Rodzica do genomu Dziecka
		visited[crossedMember[i]] = true;	//odznaczanie wierzcho�ka (genu) jako odwiedzonego
	}
	for (int i = 0; i < secondMember.path.size(); i++)	//p�tla "uzupe�niaj�ca" genom dziecka genami drugiego rodzica
	{		//iterujemy po kolejnych genach Rodzica2 i sprawdzamy, czy znajduje si� on ju� genomie dziecka, je�li nie to dodajemy go do dziecka
		if (!visited[secondMember.path[i]])		//sprawdzenie, czy gen znajduje si� ju� w genomie dziecka
			crossedMember.push_back(secondMember.path[i]);	//dodanie genu drugiego Rodzica do genomu Dziecka
	}
	delete[] visited;		//usuni�cie dynamicznej tablicy odwiedzin
	populationMember temp;	//inicjalizacja dziecka
	temp.path = crossedMember;	//przypisanie dziecku genomu po krzy�owaniu jako jego w�asnego
	temp.cost = calculatePathCost(temp.path);	//obliczenie kosztu przej�cia po drodze z genomu i przypisanie jej dziecku przy pomocy metody calculatePathCost()
	return temp;	//zwr�cenie dziecka
}

populationMember EvolutionAlgorithm::generateMutationFirstMethod(populationMember member)	//metoda przeprowadzaj�ca pierwszy rodzaj mutacji (SWAP) na osobniku podanym jako parametr metody
{
	int a, b;
	do
	{	//losowanie dw�ch gen�w (wierzcho�k�w), kt�re maj� zosta� zamienione miejscami
		a = rand() % graph.getVertices();
		b = rand() % graph.getVertices();
	} while (a == b);	//losowanie tak d�ugo, a� b�d� r�ne
	std::swap(member.path[a], member.path[b]);	//zamiana wierzcho�k�w miejscami w wektorze symbolizuj�cym drog�
	member.cost = calculatePathCost(member.path);	//obliczenie kosztu przej�cia dla nowej drogi
	return member;	//zwr�cenie zmodyfikowanego osobnika
}

populationMember EvolutionAlgorithm::generateMutationSecondMethod(populationMember member)	//metoda przeprowadzaj�ca drugi rodzaj mutacji (SCRAMBLE) na osobniku podanym jako parametr metody
{
	int a = rand() % (graph.getVertices() - 7);		//wylosowanie pocz�tku ci�gu do wyci�cia
	std::vector<int> mutation;		//inicjalizacja wektora, kt�ry przechowywa� b�dzie ci�g zmutowany
	for (int i = a; i < a + 6; i++)
		mutation.push_back(member.path[i]);	//"wyci�cie" ci�gu 6 gen�w zaczynaj�c od wcze�niej wylosowanego
	random_shuffle(mutation.begin(), mutation.end());	//pomieszanie wyci�tego fragmentu genomu
	for (int i = a, j = 0; i < a + 6; i++, j++)	//ustawienie odpowiedniego miejsca do "wklejenia" pomieszanego fragmentu genomu
		member.path[i] = mutation[j];	//umieszczenie kolejnych gen�w w mutowanym osobniku
	member.cost = calculatePathCost(member.path);	//obliczenie kosztu przej�cia dla nowej drogi
	return member;	//zwr�cenie zmodyfikowanego osobnika
}

int EvolutionAlgorithm::calculatePathCost(std::vector<int> permutation)		//metoda obliczaj�ca koszt przej�cia po drodze podawanej jako parametr metody
{
	int cost = 0;	//ustawienie pocz�tkowego kosztu jako 0
	for (int i = 0; i < permutation.size() - 1; i++)	//iteracja po kolejnych wierzcho�kach drogi
	{
		int currentVert = permutation.at(i);	//odczytanie aktualnego wierzcho�ka
		int nextVert = permutation.at(i + 1);	//odczytanie wierzcho�ka do kt�rego teraz nale�y przej��
		cost += graph.getGraph()[currentVert][nextVert];	//dodanie kosztu przej�cia pomi�dzy wierzcho�kami do ca�kowitego kosztu przej�cia
	}
	cost += graph.getGraph()[permutation[graph.getVertices() - 1]][permutation[0]];	//dodanie ostatniego przej�cia (wierzcho�ek ko�cowy do wierzcho�ka pocz�tkowego) do ca�kowitego kosztu przej�cia
	return cost;	//zwr�cenie obliczonego kosztu przej�cia
}

std::vector<populationMember> EvolutionAlgorithm::generatingStartPopulation()		//metoda generuj�ca populacj� pocz�tkow�
{
	std::vector<populationMember> startPopulation;	//inicjalizacja wektora przechowuj�cego populacj� startow� (wektor struktur symbolizuj�cych osobniki)
	for (int i = 0; i < startPopulationSize; i++)
	{
		populationMember temp;	//inicjalizacja osobnika
		temp.path = generatingPermutation();	//generacja losowego przej�cia dla osobnika
		temp.cost = calculatePathCost(temp.path);	//obliczenie kosztu przej�cia po drodze zapisanej w osobniku
		startPopulation.push_back(temp);	//dodanie osobnika do populacji (wektora struktur)
	}
	return startPopulation;		//zwr�cenie populacji startowej (wektora struktur - osobnik�w)
}

std::vector<int> EvolutionAlgorithm::generatingPermutation()		//metoda generuj�ca losow� permutacj� wierzcho�k�w grafu
{
	std::vector<int> permutation;	//inicjalizacja wektora int�w do przechowywania kolejnych wierzcho�k�w w drodze
	for (int i = 0; i < graph.getVertices(); i++)
		permutation.push_back(i);	//dodanie wszystkich wierzcho�k�w grafu do wektora
	random_shuffle(permutation.begin(), permutation.end());	//losowe pomieszanie wierzcho�k�w
	return permutation;	//zwr�cenie wylosowanej drogi
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
	graph.setVertices(givenGraph.getVertices());	//ustawienie wielko�ci grafu - ilo�ci jego wierzcho�k�w
	graph.setGraphFrag(givenGraph);		//ustawienie grafu
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
