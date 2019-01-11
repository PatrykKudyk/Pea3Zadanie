#pragma once
#include <vector>

class TimeMeasure
{
private: 
	double PCFreq;
	__int64 CounterStart;
public:
	TimeMeasure();
	~TimeMeasure();
	double getCounter() const;	//metoda zwracaj�ca aktualny stan licznika
	void startCounting();		//metoda zeruj�ca licznik i startuj�ca go
	void saveToFile(std::vector<double>& czasy, std::string filename);	//metoda zapisuj�ca wektor podany jako parametr pod nazw� pliku podan� jako parametr
	void saveToFile(std::vector<std::vector<int>>& czasy, std::string filename);	//metoda zapisuj�ca wektor wektor�w podany jako parametr pod nazw� pliku podan� jako parametr
};

