#include "Relation.h"
#include <memory>
#include "Consts.h"
#include "Neuron.h"

Relation::Relation(shared_ptr<Neuron> items1, shared_ptr<Neuron> items2) {
	item1 = items1;
	item2 = items2;

	changedStrength = 0;
	strength = 0;
}

///뉴런 1의 출력 값을 뉴런 2로 이동시킴
void Relation::SendValue() {
	item2->prevalues->push_back(item1->value * strength);
}
void Relation::ChangeStrength(float errRating) {

	changedStrength = strength - (item1->value * strength * errRating * Consts::learningRate);
}