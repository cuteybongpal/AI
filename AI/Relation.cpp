#include "Relation.h"
#include <memory>

Relation::Relation(shared_ptr<Neuron> items1, shared_ptr<Neuron> items2) {
	this->item1 = items1;
	this->item2 = items2;
}

void Relation::SendValue() {
	item2->prevalues->push_back(item1->value * strength);
}