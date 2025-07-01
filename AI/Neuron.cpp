#include "Neuron.h"
#include <cmath>
#include <list>
#include <memory>

using namespace std;
//다른 뉴런들에게서 받은 출력값들의 합을 tanh함수에 넣어 정규화 후, value에 넣어줌.
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
	prevalues->clear();
}

Neuron::Neuron() {
	prevalues = new list<float>();
	Backrelation = make_shared<list<shared_ptr<Relation>>>();
	Forrelation = make_shared<list<shared_ptr<Relation>>>();
	prevalue = 0;
	value = 0;
}