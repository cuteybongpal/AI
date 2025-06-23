#pragma once
#include <list>
#include "Neuron.h"
#include "Relation.h"

using namespace std;

class Layer
{
public:
	list<shared_ptr<Neuron>> Neurons;
private:
	int layerIndex;
};

