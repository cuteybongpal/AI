#include "Neuron.h"
#include <cmath>


void Neuron::setValue()
{
	float sum = 0;
	list<float>::iterator it;
	
	for (it = prevalues->begin(); it != prevalues->end(); it++)
	{
		sum += *it;
	}
	float value = std::tanh(sum);

	this -> value = value;
}

Neuron::Neuron() {
	this->prevalues = new list<float>();
	prevalue = 0;
	value = 0;
}