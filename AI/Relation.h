#pragma once
#include <memory>

using namespace std;
class Neuron;

class Relation
{
public:
	shared_ptr<Neuron> item1;
	shared_ptr<Neuron> item2;

	float strength;

	Relation(shared_ptr<Neuron> items1, shared_ptr<Neuron> items2);
	void SendValue();

	void ChangeStrength(float errRating);
};