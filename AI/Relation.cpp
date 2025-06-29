#include "Relation.h"
#include <memory>
#include "Consts.h"
#include "Neuron.h"

Relation::Relation(shared_ptr<Neuron> items1, shared_ptr<Neuron> items2) {
	item1 = items1;
	item2 = items2;
}

void Relation::SendValue() {
	item2->prevalues->push_back(item1->value * strength);
}
void Relation::ChangeStrength(float errRating) {

	strength = strength - (((item1->value * strength)/item2->prevalue) * errRating) * Consts::learningRate;
}