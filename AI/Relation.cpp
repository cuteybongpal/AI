#include "Relation.h"


Relation::Relation(Neuron* items1, Neuron* items2) {
	this->item1 = items1;
	this->item2 = items2;
}

void Relation::SendValue() {
	item2->prevalue->push_back(item1->value * strength);
}