#include "Neuron.h"
#include <cmath>


void Neuron::setValue()
{
	float sum = 0;
	list<float>::iterator it;
	
	for (it = this->prevalue->begin(); it != this->prevalue->end(); it++)
	{
		sum += *it;
	}
	float value = std::tanh(sum);

	this -> value = value;
}

Neuron::Neuron() {
	this->prevalue = new list<float>();
}