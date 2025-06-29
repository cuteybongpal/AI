#include "Neuron.h"
#include <cmath>
#include <list>
#include <memory>

using namespace std;

void Neuron::setValue()
{
	float sum = 0;
	list<float>::iterator it;
	
	for (it = prevalues->begin(); it != prevalues->end(); it++)
	{
		sum += *it;
	}
	float value = tanh(sum);

	this -> value = value;
}

Neuron::Neuron() {
	prevalues = new list<float>();
	Backrelation = make_shared<list<shared_ptr<Relation>>>();
	Forrelation = make_shared<list<shared_ptr<Relation>>>();
	prevalue = 0;
	value = 0;
}