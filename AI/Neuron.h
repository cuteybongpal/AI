#pragma once
#include <list>
#include <memory>

using namespace std;
class Relation;

class Neuron
{
public:
	//�ٸ� ���̾�鿡�Լ� ���� ����
	list<float>* prevalues;
	float prevalue;
	//�ٸ� ���̾�鿡�Լ� ���� ���� ���� ������ ������ ��
	float value;
	void setValue();

	shared_ptr<list<shared_ptr<Relation>>> Forrelation;
	shared_ptr<list<shared_ptr<Relation>>> Backrelation;

	Neuron();
};

