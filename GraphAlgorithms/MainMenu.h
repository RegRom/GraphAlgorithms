#pragma once
#include "IncidenceMatrix.h"
#include "NeighboursList.h"

class MainMenu
{
private:
	std::string greetingMessage;
	std::string primMenu;
	std::string dijkstraMenu;
	std::chrono::high_resolution_clock::time_point t1, t2;
	long double results[101];
	IncidenceMatrix *matrix;
	NeighboursList *list;
public:
	MainMenu();
	~MainMenu();
	void calcAverage();
	void setGreetingMessage();
	std::string getGreetingMessage();
	void setPrimMenu();
	std::string getPrimMenu();
	void setDijkstraMenu();
	std::string getDijkstraMenu();
	void saveResultsToFile(std::string filePath);
	double saveCountTime();
	void primExperiments(char option);
	void dijkstraExperiments(char option);
	void primTimeExperiment(int size, float density);
	void dijkstraTimeExperiments(int size, float density);
};

