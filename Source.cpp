#include <iostream>
#include "Item.h"
#include "GeneticAlgorithm.h"
#include <vector>
#include <ctime>
#include <cstdio>
#include <stdlib.h>

using namespace std;

int main()
{
	//input
	int pop = 3000;
	float kill = 0.2;
	float select = 0.25;
	int generations = 3000;
	int maxweight;
	int items;
	cin >> maxweight;
	cin >> items;
	srand(time(NULL));
	std::clock_t start;
	double duration;
	start = std::clock();
	GeneticAlgorithm program(maxweight, pop, generations, kill, select, items);
	cin >> program;
	program.Run();
	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Total computation time: " << duration << '\n';
	cin >> pop;
	return 0;
}