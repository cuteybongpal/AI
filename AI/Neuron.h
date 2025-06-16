#pragma once
#include <list>
using namespace std;

class Neuron
{
public:
	//다른 레이어들에게서 받은 값들
	list<float>* prevalues;
	float prevalue;
	//다른 레이어들에게서 받은 값을 토대로 연산을 진행한 값
	float value;
	void setValue();

	Neuron();
};

