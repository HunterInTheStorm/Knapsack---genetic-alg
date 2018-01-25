#pragma once
#include <vector>
#include "Item.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>

class KnapSackGene
{
private:
	int maxWeight;
	int currentWeight;
	int value;
	void setMaxWeight(int mw);
	void fillKnapSackAtRandom(std::vector<Item>& items);
	void removeWeight(int w);
	void RemoveValue(int v);
	void addValue(int v);
	void addWeight(int w);

public:
	bool addItem(Item& item, int itemIndex);
	void removeItem(int itemAt, std::vector<Item>& items);
	bool willFit(Item& item);
	std::vector<int> itemIndex;
	KnapSackGene(int mw, std::vector<Item>& items);
	KnapSackGene();
	~KnapSackGene();
	int getValue() const;
	int getCurrenWight() const;
	int getMaxWeight();
	float getRatio() const;
	KnapSackGene crossover(KnapSackGene& other, std::vector<Item>& items);
	void mutation(std::vector<Item>& items);
	friend bool operator<(const KnapSackGene& lhs, const KnapSackGene& rhs);
	friend bool operator>(const KnapSackGene& lhs, const KnapSackGene& rhs);
	//inline const bool operator>=(const KnapSackGene& rhs)const;
	//inline const bool operator<=(const KnapSackGene& rhs)const;
	friend std::ostream& operator<<(std::ostream& out, KnapSackGene& ks);
};

