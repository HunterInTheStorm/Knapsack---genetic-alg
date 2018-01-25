#include "KnapSackGene.h"



KnapSackGene::KnapSackGene(int mw, std::vector<Item>& items)
{
	this->setMaxWeight(mw);
	this->value = 0;
	this->currentWeight = 0;
	this->itemIndex = std::vector<int>();
	this->fillKnapSackAtRandom(items);
}

KnapSackGene::KnapSackGene() : KnapSackGene(100, std::vector<Item>())
{

}

KnapSackGene::~KnapSackGene()
{
}

bool KnapSackGene::addItem(Item& item, int itemIndex)
{
	if (this->willFit(item))
	{
		this->addValue(item.getValue());
		this->addWeight(item.getWeight());
		this->itemIndex.push_back(itemIndex);
		return true;
	}
	return false;
}

void KnapSackGene::removeItem(int itemAt, std::vector<Item>& items)
{
	Item item = items[this->itemIndex[itemAt]];
	this->RemoveValue(item.getValue());
	this->removeWeight(item.getWeight());
	this->itemIndex.erase(this->itemIndex.begin() + itemAt);
}


void KnapSackGene::setMaxWeight(int mw)
{
	this->maxWeight = mw;
}

void KnapSackGene::addValue(int v)
{
	this->value += v;
}

void KnapSackGene::RemoveValue(int v)
{
	this->value -= v;
}

void KnapSackGene::addWeight(int w)
{
	this->currentWeight += w;
}

void KnapSackGene::removeWeight(int w)
{
	this->currentWeight -= w;
}

void KnapSackGene::fillKnapSackAtRandom(std::vector<Item>& items)
{
	int* itemListIndex = new int[items.size()];
	int size = items.size();
	for (int i = 0; i < size; i++)
	{
		itemListIndex[i] = i;
	}
	for (int i = 0; i < size - 1; i++)
	{
		int random = i + rand() % (size - i);
		int temp = itemListIndex[i];
		itemListIndex[i] = itemListIndex[random];
		itemListIndex[random] = temp;
	}
	for (int i = 0; i < size; i++)
	{
		Item& item = items[itemListIndex[i]];
		this->addItem(item, itemListIndex[i]);
		if (this->currentWeight == this->maxWeight)
		{
			break;
		}
	}
}

int KnapSackGene::getValue() const
{
	return this->value;
}

int KnapSackGene::getCurrenWight() const
{
	return this->currentWeight;
}

int KnapSackGene::getMaxWeight()
{
	return this->maxWeight;
}

float KnapSackGene::getRatio() const
{
	return float(this->value) / float(this->currentWeight);
}

bool KnapSackGene::willFit(Item& item)
{
	return this->currentWeight + item.getWeight() <= this->maxWeight;
}

KnapSackGene KnapSackGene::crossover(KnapSackGene& other, std::vector<Item>& items)
{
	KnapSackGene newGene(this->maxWeight, std::vector<Item>());
	std::unordered_map<int, bool> mymap;
	int maxSize = std::max(this->itemIndex.size(), other.itemIndex.size());
	for (int i = 0; i < maxSize; i++)
	{
		int randomKS = rand() % 2;
		if (!mymap[itemIndex[i]] && i < this->itemIndex.size() && randomKS == 0)
		{
			Item item = items[this->itemIndex[i]];
			if (newGene.addItem(item, this->itemIndex[i]))
			{
				mymap[itemIndex[i]] = true;
			}
			else
			{
				randomKS = 1;
			}
		}
		if (randomKS == 1 && i < other.itemIndex.size() && !mymap[other.itemIndex[i]])
		{
			Item item = items[other.itemIndex[i]];
			if (newGene.addItem(item, other.itemIndex[i]))
			{
				mymap[other.itemIndex[i]] = true;
			}
		}
		if (this->currentWeight == this->maxWeight)
		{
			break;
		}
	}
	return newGene;
}

void KnapSackGene::mutation(std::vector<Item>& items)
{
	if ((rand() % 100) < 5)
	{
		std::unordered_map<int, bool> mymap;
		for (std::vector<int>::iterator i = this->itemIndex.begin(); i != this->itemIndex.end(); i++)
		{
			mymap[*i] = true;
		}

		int removeEleemntAt = rand() % this->itemIndex.size();
		this->removeItem(removeEleemntAt, items);

		int index = 0;
		for (std::vector<Item>::iterator it = items.begin(); it != items.end(); it++)
		{
			Item& item = *it;
			if (!mymap[index] && this->willFit(item))
			{
				this->addItem(item, index);
				mymap[index] = true;
			}
			index++;
		}
	}
}

bool operator<(const KnapSackGene& lhs, const KnapSackGene& rhs)
{
	return lhs.getValue() < rhs.getValue();
}

bool operator>(const KnapSackGene& lhs, const KnapSackGene& rhs)
{
	return rhs < lhs;
}
//inline const bool KnapSackGene::operator>=(const KnapSackGene& rhs)const
//{
//	return !(this->operator<(rhs));
//}
//inline const bool KnapSackGene::operator<=(const KnapSackGene& rhs)const
//{
//	return !(this->operator>(rhs));
//}


std::ostream& operator<<(std::ostream& out, KnapSackGene& ks)
{
	for (std::vector<int>::iterator i = ks.itemIndex.begin(); i != ks.itemIndex.end(); i++)
	{
		out << *i << " ";
	}
	return out;
}

