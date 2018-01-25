#pragma once
#include <iostream>
#include "Item.h"
#include "KnapSackGene.h"
#include <algorithm>
#include <functional>

class GeneticAlgorithm
{
private:
	int maxWeight;
	int population;
	int generations;
	float killOff;
	float selectOff;
	int itemNum;
	std::vector<Item> items;
	std::vector<KnapSackGene> genes;
	void setMaxWeight(int mw);
	void setPopulation(int pop);
	void setGenerations(int gen);
	void setKillOff(float kill);
	void setSelectOff(float select);
	void setItemNum(int num);

public:
	GeneticAlgorithm(int mx, int pop, int gen, float kill, float select, int itemNumber);
	~GeneticAlgorithm();
	int getMaxWeight();
	int getPopulation();
	int getGenerations();
	float getKillOff();
	float getSelectOff();
	int getItemNum();
	void Run();
	void createGenes();
	void fitnessFunction(int currentGeneration);
	int selection();
	void killOffExtraPopulation();
	void crossover(int children);
	friend std::istream& operator >> (std::istream& in, GeneticAlgorithm& alg);
};

