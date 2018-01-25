#pragma once
class Item
{
private:
	int weight;
	int value;
	void setWeight(int w);
	void setValue(int v);
public:
	Item(int w, int v);
	Item();
	int getWeight();
	int getValue();
	float getRation();
	~Item();
};

