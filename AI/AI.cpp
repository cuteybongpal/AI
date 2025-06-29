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

void Setup();
int classifyNumber();
float getAccuracy();

int main()
{
    //초기 세팅
    Setup();
    //가중치를 통해 숫자 분류
     
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
            cout << strengths[index] << endl;

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

int classifyNumber() 
{
    
}
float getAccuracy() {

}