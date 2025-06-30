#include <iostream>
#include "Neuron.h"
#include "Relation.h"
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>
#include "ImageLoader.h"
#include <fstream>
#include <string>
#include <direct.h>
#include "Strength.h"
#include <filesystem>
#include <fstream>
#include <random>

using namespace std;

list<shared_ptr<Neuron>> inputLayer = list<shared_ptr<Neuron>>();
list<shared_ptr<Neuron>> hiddenLayer1 = list<shared_ptr<Neuron>>();
list<shared_ptr<Neuron>> hiddenLayer2 = list<shared_ptr<Neuron>>();
list<shared_ptr<Neuron>> outputLayer = list<shared_ptr<Neuron>>();

vector<int> results = vector<int>();
vector<int> answers = vector<int>();

void Setup();
void classifyNumber(const char* path);
float getAccuracy();

int main()
{
    //초기 세팅
    Setup();
    //가중치를 통해 숫자 분류
    classifyNumber("../training/0/1000.png");
    //역전파(traning상태일때만)

}

void Setup()
{
    //계층 별로 레이어 생성하기
    for (int i = 0; i < 28; i++)
        for (int j = 0; j < 28; j++)
            inputLayer.push_back(make_shared<Neuron>());

    for (int i = 0; i < 15; i++)
        hiddenLayer1.push_back(make_shared<Neuron>());

    for (int i = 0; i < 15; i++)
        hiddenLayer2.push_back(make_shared<Neuron>());

    for (int i = 0; i < 10; i++)
        outputLayer.push_back(make_shared<Neuron>());

    //Relation 연결
    //todo : 가중치 넣어주기
    list<shared_ptr<Neuron>>::iterator iter1;

    int index = 0;
    vector<float> strengths = Strength::LoadStrength(0);

    for (iter1 = inputLayer.begin(); iter1 != inputLayer.end(); iter1++)
    {
        list<shared_ptr<Neuron>>::iterator iter2;

        for (iter2 = hiddenLayer1.begin(); iter2 != hiddenLayer1.end(); iter2++)
        {
            shared_ptr<Relation> rel = make_shared<Relation>(*iter1, *iter2);
            rel->strength = strengths[index];

            iter1->get()->Forrelation->push_back(rel);
            iter2->get()->Backrelation->push_back(rel);

            index++;
        }
    }

    index = 0;
    strengths = Strength::LoadStrength(1);
    for (iter1 = hiddenLayer1.begin(); iter1 != hiddenLayer1.end(); iter1++)
    {
        list<shared_ptr<Neuron>>::iterator iter2;

        for (iter2 = hiddenLayer2.begin(); iter2 != hiddenLayer2.end(); iter2++)
        {
            shared_ptr<Relation> rel = make_shared<Relation>(*iter1, *iter2);
            rel->strength = strengths[index];

            iter1->get()->Forrelation->push_back(rel);
            iter2->get()->Backrelation->push_back(rel);
            index++;
        }
    }

    index = 0;
    strengths = Strength::LoadStrength(2);
    for (iter1 = hiddenLayer2.begin(); iter1 != hiddenLayer2.end(); iter1++)
    {
        list<shared_ptr<Neuron>>::iterator iter2;

        for (iter2 = outputLayer.begin(); iter2 != outputLayer.end(); iter2++)
        {
            shared_ptr<Relation> rel = make_shared<Relation>(*iter1, *iter2);
            rel->strength = strengths[index];

            iter1->get()->Forrelation->push_back(rel);
            iter2->get()->Backrelation->push_back(rel);
            index++;
        }
    }
}

void classifyNumber(const char* path)
{
    vector<float> imageVector = ImageLoader::LoadPNG(path);

    list<shared_ptr<Neuron>>::iterator iter;
    int index = 0;

    for (iter = inputLayer.begin(); iter != inputLayer.end(); iter++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter;
        selectedNeuron->value = imageVector[index];
        index++;
        
        list<shared_ptr<Relation>>::iterator iter2;
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
            iter2->get()->SendValue();
    }

    for (iter = hiddenLayer1.begin(); iter != hiddenLayer1.end(); iter++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter;
        selectedNeuron->setValue();

        list<shared_ptr<Relation>>::iterator iter2;
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
            iter2->get()->SendValue();
    }

    for (iter = hiddenLayer2.begin(); iter != hiddenLayer2.end(); iter++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter;
        selectedNeuron->setValue();

        list<shared_ptr<Relation>>::iterator iter2;
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
            iter2->get()->SendValue();
    }
    for (iter = outputLayer.begin(); iter != outputLayer.end(); iter++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter;
        selectedNeuron->setValue();

        cout << selectedNeuron->value << endl;
    }

}
float getAccuracy() {
    return 0;
}