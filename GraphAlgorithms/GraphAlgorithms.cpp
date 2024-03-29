// GraphAlgorithms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrix.h"
#include "NeighboursList.h"
#include "MainMenu.h"

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

void normalMenu(int max, int min)
{
	MainMenu *menu = new MainMenu();						//Tworzymy obiekt do zarz�dzania grafami
	while (true) {
		int Option = 0;											//Wybór algorytmu, który chcemy testować
		char expOption = 0;										//Wybór konkretnej czynnoąci jaką chcemy wykonać
		std::cout << menu->getGreetingMessage();
		Option = checkInt(0, 7);								//Sprawdzamy czy wprowadzony wybór mie�ci si� w zbiorze mo�liwych

		if (Option == 1)										
		{
			std::cout << menu->getPrimMenu();
			std::cin >> expOption;
			menu->primExperiments(expOption);

		}
		else if (Option == 2)
		{
			std::cout << menu->getDijkstraMenu();
			std::cin >> expOption;
			menu->dijkstraExperiments(expOption);
		}
		else if (Option == 0)									//Wyj�cie z programu
		{
			delete menu;
			exit(0);
		}
		getchar();
		system("cls");
	}
}




int main()
{
	static const int MIN = 1;											//Minimalny rozmiar grafu
	static const int MAX = 20000;

	std::cout << "Welcome to Graph Algorithms Testing Program\n";


	normalMenu(MIN, MAX);
	MainMenu *menu = new MainMenu();
	menu->primTimeExperiment(125, 0.99);
	//menu->dijkstraTimeExperiments(50, 0.99);
	std::cout << "Done :)";

    return 0;
}

