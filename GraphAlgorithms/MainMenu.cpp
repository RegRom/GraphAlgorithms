#include "stdafx.h"
#include "MainMenu.h"

extern int checkInt(int min, int max);

MainMenu::MainMenu()
{
	setGreetingMessage();
	setPrimMenu();
	setDijkstraMenu();
}


MainMenu::~MainMenu()
{
	delete list;
	delete matrix;
}

void MainMenu::calcAverage()
{
	long double sum = 0;
	long double avg = 0;
	for (int i = 0; i < 100; i++)
	{
		sum += results[i];
	}
	avg = sum / 100;
	results[100] = avg;
}

//Metoda ustawiająca tekst głównego menu
void MainMenu::setGreetingMessage()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a następnie pobieramy je do jednego stringa
	ss << "\n[1] Find the MST using Prim Algorithm" << "\n[2] Find the shortest path using Dijkstra Algorithm"; 
	ss << "\n[0] Exit the program" << "\nYour choice: ";
	this->greetingMessage = ss.str();
}

//Metoda zwracająca tekst głównego menu
std::string MainMenu::getGreetingMessage()
{
	return this->greetingMessage;
}

void MainMenu::setPrimMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a następnie pobieramy je do jednego stringa
	ss << "Prim algorithm:\n";
	ss << "[1] Read a neighbours list from file\n" << "[2] Read a incidence matrix from file\n" << "[3] Generate a neighbours list randomly\n";
	ss << "[4] Generate a incidence matrix randomly\n" << "[5] Display a neighbours list\n" << "[6] Display a incidence matrix\n";
	ss << "[7] Prim algorithm for neighbours list\n" << "[8] Prim algorithm for incidence matrix\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->primMenu = ss.str();
}

std::string MainMenu::getPrimMenu()
{
	return this->primMenu;
}

void MainMenu::setDijkstraMenu()
{
	std::stringstream ss;

	//Umieszczamy kolejne stringi w stringstream, a następnie pobieramy je do jednego stringa
	ss << "Dijkstra algorithm:\n";
	ss << "[1] Read a neighbours list from file\n" << "[2] Read a incidence matrix from file\n" << "[3] Generate a neighbours list randomly\n";
	ss << "[4] Generate a incidence matrix randomly\n" << "[5] Display a neighbours list\n" << "[6] Display a incidence matrix\n";
	ss << "[7] Dijkstra algorithm for neighbours list\n" << "[8] Dijkstra algorithm for incidence matrix\n" << "[q] Return to main menu\n" << "\nYour choice: ";
	this->dijkstraMenu = ss.str();
}

std::string MainMenu::getDijkstraMenu()
{
	return this->dijkstraMenu;
}

void MainMenu::saveResultsToFile(std::string filePath)
{
	std::fstream file;						//tworzymy zmienn� plikow�
	file.open(filePath, std::ios::out);		//otwieramy do zapisu
	if (file.good()) {						//sprawdzamy czy plik nie jest uszkodzony
		for (int i = 0; i < 101; i++)
		{
			file << std::fixed;										//wy��czamy notacj� naukow�
			file << std::setprecision(8) << results[i] << "\n";		//ustawiamy ilosc miejsc po przecinku w wyniku i zapisujemy wynik
		}
		file.close();
	}
}

//Metoda zapisuj�ca czas wykonania operacji na strukturze
double MainMenu::saveCountTime()
{
	namespace clk = std::chrono;		//tworzenie aliasu dla przestrzeni nazw
	clk::high_resolution_clock::rep time = clk::duration_cast<clk::nanoseconds>(t2 - t1).count();		//obliczamy czas wykonania odejmuj�c czas pocz�tkowy od koncowego
	long double expTime = (long double)time * pow(10, -9);												//konwertujemy wynik w nanosekundach do sekund
	return expTime;
}

void MainMenu::primExperiments(char option)
{
	int val;
	float dens;
	switch (option)
	{
	case '1':
		list = NeighboursList::readGraphFromFile("neighbours.txt", false);							//wczytywanie listy sąsiedztwa z pliku
		break;
	case '2':
	{
		matrix = IncidenceMatrix::readGraphFromFile("neighbours.txt", false);						//wczytywanie macierzy incydencji z pliku
		break;
	}
	break;
	case '3':
	{
		std::cout << "Input a graph size: ";
		val = checkInt(1, 20000);

		std::cout << "Input a density as percents: ";
		dens = checkInt(1, 100);

		list = new NeighboursList(val, dens / 100, false);
		list->randomFillGraph();
	}
	break;
	case '4':
	{
		std::cout << "Input a graph size: ";
		val = checkInt(1, 20000);

		std::cout << "Input a density as percents: ";
		dens = checkInt(1, 100);

		matrix = new IncidenceMatrix(val, dens / 100, false);
		matrix->randomFillGraph();
	}
	break;
	case '5':
	{
		list->display();
		getchar();
	}
	break;
	case '6':
	{
		matrix->display();
		getchar();
	}
	break;
	case '7':
	{
		NeighboursList *tree = NeighboursList::primAlgorithm(list);
		tree->display();
		getchar();
		delete tree;
	}
	break;
	case '8':
	{
		NeighboursList *tree = IncidenceMatrix::primAlgorithm(matrix);
		tree->display();
		getchar();
		delete tree;											//Usuwamy drzewo rozpinające
	}
	break;
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
}

void MainMenu::dijkstraExperiments(char option)
{
	int val = 0, size = 0, begin = 0, end = 0;
	float dens = 0;
	switch (option)
	{
	case '1':
		list = NeighboursList::readGraphFromFile("neighbours.txt", true);							//wczytywanie listy sąsiedztwa z pliku
		break;
	case '2':
	{
		matrix = IncidenceMatrix::readGraphFromFile("neighbours.txt", true);						//wczytywanie macierzy incydencji z pliku
		break;
	}
	break;
	case '3':
	{
		std::cout << "Input a graph size: ";
		size = checkInt(1, 20000);

		std::cout << "Input a density as percents: ";
		dens = checkInt(1, 100);

		list = new NeighboursList(size, dens / 100, true);
		list->randomFillGraph();
	}
	break;
	case '4':
	{
		std::cout << "Input a graph size: ";
		size = checkInt(1, 20000);

		std::cout << "Input a density as percents: ";
		dens = checkInt(1, 100);

		matrix = new IncidenceMatrix(size, dens / 100, true);
		matrix->randomFillGraph();
	}
	break;
	case '5':
	{
		list->display();
		getchar();
	}
	break;
	case '6':
	{
		matrix->display();
		getchar();
	}
	break;
	case '7':
	{
		std::cout << "Input begin vertex: ";
		begin = checkInt(1, list->getSize());

		std::cout << "Input end vertex: ";
		end = checkInt(1, list->getSize());

		NeighboursList::dijkstraAlgorithm(list, begin, end);
	}
	break;
	case '8':
	{
		std::cout << "Input begin vertex: ";
		begin = checkInt(1, matrix->getSize()-1);

		std::cout << "Input end vertex: ";
		end = checkInt(1, matrix->getSize()-1);

		IncidenceMatrix::dijkstraAlgorithm(matrix, begin, end);
	}
	break;
	case 'q':
		return;
	default:
		std::cout << "An unidentified option has been chosen, please input correct parameter to perfom an action!\n";
	}
}
