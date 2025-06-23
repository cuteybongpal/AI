#pragma once
#include "Neuron.h"
#include <memory>

class Relation
{
public:
	std::shared_ptr<Neuron> item1;
	std::shared_ptr<Neuron> item2;

	float strength;

	Relation(shared_ptr<Neuron> items1, shared_ptr<Neuron> items2);
	void SendValue();

	void ChangeStrength(float errRating);
};

