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
	double getCounter() const;
	void startCounting();
	void saveToFile(std::vector<double>& czasy, std::string filename);
	void saveToFile(std::vector<std::vector<int>>& czasy, std::string filename);
};

