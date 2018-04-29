// GraphAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrix.h"

int checkInt(int min, int max)
{
	int input;
	while (!(std::cin >> input) || (input < min) || (input > max) || std::cin.peek() != '\n')
	{
		std::cout << "You must input a whole number between " << min << " and " << max << "!\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return input;
}

int main()
{
	IncidenceMatrix *matrix = new IncidenceMatrix(10, 0.25, false);
	matrix->randomFillGraph();
	matrix->display();

    return 0;
}

