#include "Item.h"

Item::Item(int w, int v)
{
	this->setValue(v);
	this->setWeight(w);
}

Item::Item() : Item(1, 1){}

Item::~Item()
{
}

void Item::setValue(int v)
{
	this->value = v;
}

void Item::setWeight(int w)
{
	this->weight = w;
}

int Item::getWeight()
{
	return this->weight;
}

int Item::getValue()
{
	return this->value;
}

float Item::getRation()
{
	return float(this->value / this->weight);
}
