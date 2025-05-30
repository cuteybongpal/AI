#pragma once
#include "Neuron.h"

class Relation
{
public:
	Neuron* item1;
	Neuron* item2;

	float strength;

	Relation(Neuron* items1, Neuron* items2);

};

