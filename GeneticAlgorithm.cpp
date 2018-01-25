#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int mx, int pop, int gen, float kill, float select, int itemNumber)
{
	this->setMaxWeight(mx);
	this->setKillOff(kill);
	this->setGenerations(gen);
	this->setPopulation(pop);
	this->setSelectOff(select);
	this->setItemNum(itemNumber);
	this->genes = std::vector<KnapSackGene>();
	this->items = std::vector<Item>();
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::setItemNum(int num)
{
	this->itemNum = num;
}

int GeneticAlgorithm::getItemNum()
{
	return this->itemNum;
}

void GeneticAlgorithm::setMaxWeight(int mw)
{
	this->maxWeight = mw;
}

void GeneticAlgorithm::setPopulation(int pop)
{
	this->population = pop;
}

void GeneticAlgorithm::setGenerations(int gen)
{
	this->generations = gen;
}

void GeneticAlgorithm::setKillOff(float kill)
{
	this->killOff = kill;
}

void GeneticAlgorithm::setSelectOff(float select)
{
	this->selectOff = select;
}

int GeneticAlgorithm::getMaxWeight()
{
	return this->maxWeight;
}

int GeneticAlgorithm::getPopulation()
{
	return this->population;
}

int GeneticAlgorithm::getGenerations()
{
	return this->generations;
}

float GeneticAlgorithm::getKillOff()
{
	return this->killOff;
}

float GeneticAlgorithm::getSelectOff()
{
	return this->selectOff;
}

void GeneticAlgorithm::fitnessFunction(int currentGeneration)
{
	sort(this->genes.begin(), this->genes.end(), std::greater<KnapSackGene>());
	int temp = generations / 4;
	if (currentGeneration == 10 || currentGeneration == generations || currentGeneration  == temp || currentGeneration == temp*2 || currentGeneration == temp * 3)
	{
		KnapSackGene& best = this->genes.front();
		//std::cout << best;
		std::cout << "GENERATION: " << currentGeneration << " VALUE: " << best.getValue() << "  WEIGHT: " << best.getCurrenWight() << std::endl;
	}
}

int GeneticAlgorithm::selection()
{
	int killed = this->killOff * this->genes.size();
	for (int i = killed; i > 0; i--)
	{
		this->genes.pop_back();
	}
	return this->genes.size() * this->selectOff;
}

void GeneticAlgorithm::crossover(int children)
{
	for (int i = 0; i < children; i += 2)
	{
		KnapSackGene& gen1 = this->genes[i];
		KnapSackGene& gen2 = this->genes[i + 1];
		for (int i = 0; i < 2; i++)
		{
			KnapSackGene& child = gen1.crossover(gen2, this->items);
			child.mutation(this->items);
			this->genes.push_back(child);
		}
	}
}

void GeneticAlgorithm::killOffExtraPopulation()
{
	while (this->genes.size() >= this->population)
	{
		this->genes.pop_back();
	}
}

void GeneticAlgorithm::Run()
{
	this->createGenes();
	for (int i = 1; i <= this->generations; i++)
	{
		this->fitnessFunction(i);
		this->killOffExtraPopulation();
		int newPop = this->selection();
		this->crossover(newPop);
	}
}

void GeneticAlgorithm::createGenes()
{
	for (int i = 0; i < this->population; i++)
	{
		this->genes.push_back(KnapSackGene(this->maxWeight, this->items));
	}
}

std::istream& operator >> (std::istream& in, GeneticAlgorithm& alg)
{
	for (int i = 0; i < alg.itemNum; i++)
	{
		int w = rand() % 51 + 10;
		int v = rand() % 30 + 1;
		//int v;
		//std::cin >> v;
		//int w;
		//std::cin >> w;
		alg.items.push_back(Item(w, v));
	}
	return in;
}