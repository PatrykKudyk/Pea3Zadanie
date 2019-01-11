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
	double getCounter() const;	//metoda zwracaj¹ca aktualny stan licznika
	void startCounting();		//metoda zeruj¹ca licznik i startuj¹ca go
	void saveToFile(std::vector<double>& czasy, std::string filename);	//metoda zapisuj¹ca wektor podany jako parametr pod nazw¹ pliku podan¹ jako parametr
	void saveToFile(std::vector<std::vector<int>>& czasy, std::string filename);	//metoda zapisuj¹ca wektor wektorów podany jako parametr pod nazw¹ pliku podan¹ jako parametr
};

