#pragma once
#include <list>
using namespace std;

class Neuron
{
public:
	//�ٸ� ���̾�鿡�Լ� ���� ����
	list<float>* prevalues;
	float prevalue;
	//�ٸ� ���̾�鿡�Լ� ���� ���� ���� ������ ������ ��
	float value;
	void setValue();

	Neuron();
};

