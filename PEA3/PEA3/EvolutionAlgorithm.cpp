#include "EvolutionAlgorithm.h"
#include <algorithm>


EvolutionAlgorithm::EvolutionAlgorithm()
{
	//ustawiam poczatkowe wartosci parametrów aby mozna by³o szybciej przetestowaæ program
	stop = 100;		//stop programu ustawiony na 100 sekund
	mutationMethod = 1;	//startowa metoda mutacji ustawiona na SWAP
	mutation = 0.01;	//wspolczynnik mutacji ustawiony domyslnie na 0.01
	startPopulationSize = 100;	//populacja startowa ustawiona na 100 osobników
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
	double time = timer.getCounter();		//poranie aktualnego czasu jaki min¹³ od rozpoczêcia algorytmu
	if (time >= static_cast<double>(stop))	//sprawdzenie, czy czas jaki up³yn¹³ jest wiêkszy od czasu ustalonego jako max
		return false;		//po zwroceniu false algorytm zakonczy dzialanie

	return true;		//po zwroceniu true algorytm nadal bêdzie siê wykonywa³
}

void EvolutionAlgorithm::simulatingEvolution()		//glowna metoda klasy, która odpowiada za wykonanie symulacji
{
	timer.startCounting();		//wystartowanie licznika
	std::vector<populationMember> startPopulation = generatingStartPopulation();	//wygenerowanie populacji startowej przy pomocy metody generatingStartPopulation()
	do		//g³ówna pêtla algorytmu
	{
		int end = startPopulation.size();	//ustawienie warunku zakonczenia pêtli for jako przekroczenie wielkosci populacji
		for (int i = 0; i < end; i++)	//pêtla odpowiedzialna za przeprowadzenie krzyzowañ
		{
			if ((rand() % 1000) / 1000.0 < crossing)	//warunek sprawdzaj¹cy, czy wylosowana liczba jest mniejsza ni¿ wspó³czynnik krzy¿owania
			{
				int a, b;		
				do
				{	//losowanie 2 osobników z caloœci populacji tak, aby by³y ró¿ne
					a = rand() % startPopulation.size();
					b = rand() % startPopulation.size();
				} while (a == b);
				startPopulation.push_back(generateCrossing(startPopulation[a], startPopulation[b]));	//dodanie nowego osobnika do populacji (dziecka) podaj¹c do metody generateCrossing() dwa osobniki (rodziców)
			}
		}
		int c;
		for (int i = 0; i < startPopulation.size(); i++)	//pêtla odpowiadaj¹ca za przeprowadzenie mutacji na populacji
			if ((rand() % 1000) / 1000.0 < mutation)	//warunek sprawdzaj¹cy, czy wylosowana liczba jest mniejsza ni¿ wspó³czynnik mutacji
				switch (mutationMethod)		//sprawdzenie, która metoda mutacji zosta³a wybrana przez u¿ytkownika
				{
				//metoda pierwsza - SWAP
				case 1:	
					c = rand() % startPopulation.size();	//wylosowanie osobnika z populacji
					startPopulation[c] = generateMutationFirstMethod(startPopulation[c]);	//zmutowanie wylosowanego wczeœniej osobnika przy pomocy metody generateMutationFirstMethod()
					break;
				
				//metoda druga - SCRAMBLE
				case 2: 
					if (graph.getVertices() > 10)	//warunek sprawdzaj¹cy, czy graf posiada conajmniej 10 wierzcho³ków - dodany, bo scrambling wycina ci¹g 7 kolejnych wierzcho³ków, a nie chcia³em, ¿eby wywali³o b³¹d
					{
						c = rand() % startPopulation.size();	//wylosowanie osobnika z populacji
						startPopulation[c] = generateMutationSecondMethod(startPopulation[c]);	//zmutowanie wylosowanego wczeœniej osobnika przy pomocy metody generateMutationSecondMethod()
					}
					break;
				default:
					break;
				}

		sort(startPopulation.begin(), startPopulation.end(), compareByWeight);	//posortowanie osobników populacji wzglêdem kosztów dróg - na pocz¹tku znajduje siê najlepsze rozwi¹zanie (najmniejszy koszt)


		while (startPopulation.size() > startPopulationSize)	//pêtla usuwaj¹ca koñcowe (najgorsze) drogi tak d³ugo, a¿ wielkoœæ populacji nie bêdzie równa pocz¹tkowej
		{
			startPopulation.pop_back();		//usuniêcie ostatniego osobnika z wektora (populacji)
		}
	} while (whileCheck());	//sprawdzenie czy czas nie zosta³ przekroczony


	path = startPopulation.begin()->path;		//zapamiêtanie najlepszego osobnika z populacji jako atrybutów path i pathCost (droga i jej koszt) w obiekcie
	pathCost = startPopulation.begin()->cost;	//
}

populationMember EvolutionAlgorithm::generateCrossing(populationMember firstMember, populationMember secondMember)	//metoda tworz¹ca dziecko bêd¹ce krzy¿ówk¹ dwojga rodziców podanych jako parametry metody
{
	std::vector<int> crossedMember;			//inicjalizacja genomu dziecka
	int halfSize = graph.getVertices() / 2;		//obliczenie tego jak wiele genów musi byæ wyciête z pierwszego rodzica tak, aby by³a to po³owa wszystkich
	bool *visited = new bool[graph.getVertices()];	//inicjalizacja dynamicznej tablicy wierzcho³ków odwiedzonych
	for (int i = 0; i < graph.getVertices(); i++)
		visited[i] = false;			//wype³nienie ca³ej tablicy "false" - odpowiadaj¹cemu nieodwiedzeniu
	for (int i = 0; i < halfSize; i++)		//pêtla wycinaj¹ca pierwsz¹ po³owê genomu Pierwszego Rodzica
	{
		crossedMember.push_back(firstMember.path[i]);	//dodawanie kolejnych genów Rodzica do genomu Dziecka
		visited[crossedMember[i]] = true;	//odznaczanie wierzcho³ka (genu) jako odwiedzonego
	}
	for (int i = 0; i < secondMember.path.size(); i++)	//pêtla "uzupe³niaj¹ca" genom dziecka genami drugiego rodzica
	{		//iterujemy po kolejnych genach Rodzica2 i sprawdzamy, czy znajduje siê on ju¿ genomie dziecka, jeœli nie to dodajemy go do dziecka
		if (!visited[secondMember.path[i]])		//sprawdzenie, czy gen znajduje siê ju¿ w genomie dziecka
			crossedMember.push_back(secondMember.path[i]);	//dodanie genu drugiego Rodzica do genomu Dziecka
	}
	delete[] visited;		//usuniêcie dynamicznej tablicy odwiedzin
	populationMember temp;	//inicjalizacja dziecka
	temp.path = crossedMember;	//przypisanie dziecku genomu po krzy¿owaniu jako jego w³asnego
	temp.cost = calculatePathCost(temp.path);	//obliczenie kosztu przejœcia po drodze z genomu i przypisanie jej dziecku przy pomocy metody calculatePathCost()
	return temp;	//zwrócenie dziecka
}

populationMember EvolutionAlgorithm::generateMutationFirstMethod(populationMember member)	//metoda przeprowadzaj¹ca pierwszy rodzaj mutacji (SWAP) na osobniku podanym jako parametr metody
{
	int a, b;
	do
	{	//losowanie dwóch genów (wierzcho³ków), które maj¹ zostaæ zamienione miejscami
		a = rand() % graph.getVertices();
		b = rand() % graph.getVertices();
	} while (a == b);	//losowanie tak d³ugo, a¿ bêd¹ ró¿ne
	std::swap(member.path[a], member.path[b]);	//zamiana wierzcho³ków miejscami w wektorze symbolizuj¹cym drogê
	member.cost = calculatePathCost(member.path);	//obliczenie kosztu przejœcia dla nowej drogi
	return member;	//zwrócenie zmodyfikowanego osobnika
}

populationMember EvolutionAlgorithm::generateMutationSecondMethod(populationMember member)	//metoda przeprowadzaj¹ca drugi rodzaj mutacji (SCRAMBLE) na osobniku podanym jako parametr metody
{
	int a = rand() % (graph.getVertices() - 7);		//wylosowanie pocz¹tku ci¹gu do wyciêcia
	std::vector<int> mutation;		//inicjalizacja wektora, który przechowywaæ bêdzie ci¹g zmutowany
	for (int i = a; i < a + 6; i++)
		mutation.push_back(member.path[i]);	//"wyciêcie" ci¹gu 6 genów zaczynaj¹c od wczeœniej wylosowanego
	random_shuffle(mutation.begin(), mutation.end());	//pomieszanie wyciêtego fragmentu genomu
	for (int i = a, j = 0; i < a + 6; i++, j++)	//ustawienie odpowiedniego miejsca do "wklejenia" pomieszanego fragmentu genomu
		member.path[i] = mutation[j];	//umieszczenie kolejnych genów w mutowanym osobniku
	member.cost = calculatePathCost(member.path);	//obliczenie kosztu przejœcia dla nowej drogi
	return member;	//zwrócenie zmodyfikowanego osobnika
}

int EvolutionAlgorithm::calculatePathCost(std::vector<int> permutation)		//metoda obliczaj¹ca koszt przejœcia po drodze podawanej jako parametr metody
{
	int cost = 0;	//ustawienie pocz¹tkowego kosztu jako 0
	for (int i = 0; i < permutation.size() - 1; i++)	//iteracja po kolejnych wierzcho³kach drogi
	{
		int currentVert = permutation.at(i);	//odczytanie aktualnego wierzcho³ka
		int nextVert = permutation.at(i + 1);	//odczytanie wierzcho³ka do którego teraz nale¿y przejœæ
		cost += graph.getGraph()[currentVert][nextVert];	//dodanie kosztu przejœcia pomiêdzy wierzcho³kami do ca³kowitego kosztu przejœcia
	}
	cost += graph.getGraph()[permutation[graph.getVertices() - 1]][permutation[0]];	//dodanie ostatniego przejœcia (wierzcho³ek koñcowy do wierzcho³ka pocz¹tkowego) do ca³kowitego kosztu przejœcia
	return cost;	//zwrócenie obliczonego kosztu przejœcia
}

std::vector<populationMember> EvolutionAlgorithm::generatingStartPopulation()		//metoda generuj¹ca populacjê pocz¹tkow¹
{
	std::vector<populationMember> startPopulation;	//inicjalizacja wektora przechowuj¹cego populacjê startow¹ (wektor struktur symbolizuj¹cych osobniki)
	for (int i = 0; i < startPopulationSize; i++)
	{
		populationMember temp;	//inicjalizacja osobnika
		temp.path = generatingPermutation();	//generacja losowego przejœcia dla osobnika
		temp.cost = calculatePathCost(temp.path);	//obliczenie kosztu przejœcia po drodze zapisanej w osobniku
		startPopulation.push_back(temp);	//dodanie osobnika do populacji (wektora struktur)
	}
	return startPopulation;		//zwrócenie populacji startowej (wektora struktur - osobników)
}

std::vector<int> EvolutionAlgorithm::generatingPermutation()		//metoda generuj¹ca losow¹ permutacjê wierzcho³ków grafu
{
	std::vector<int> permutation;	//inicjalizacja wektora intów do przechowywania kolejnych wierzcho³ków w drodze
	for (int i = 0; i < graph.getVertices(); i++)
		permutation.push_back(i);	//dodanie wszystkich wierzcho³ków grafu do wektora
	random_shuffle(permutation.begin(), permutation.end());	//losowe pomieszanie wierzcho³ków
	return permutation;	//zwrócenie wylosowanej drogi
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
	graph.setVertices(givenGraph.getVertices());	//ustawienie wielkoœci grafu - iloœci jego wierzcho³ków
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
