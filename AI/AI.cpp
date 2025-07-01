
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
#include <format>
#include <random>
#include <ostream>

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
void back(int answer);

int main()
{
    vector<float> vec1 = vector<float>();
    for (int i = 0; i < 28; i++)
        for (int j = 0; i < 15; j++) 
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(-0.5, 0.5);

            float val = dis(gen);
            vec1.push_back(val);
        }
    Strength::SaveStrength(0, vec1);

    vector<float> vec2 = vector<float>();
    for (int i = 0; i < 15; i++)
        for (int i = 0; i < 15; i++)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(-0.5, 0.5);

            float val = dis(gen);
            vec2.push_back(val);
        }
    Strength::SaveStrength(1, vec2);

    vector<float> vec3 = vector<float>();
    for (int i = 0; i < 15; i++)
        for (int i = 0; i < 10; i++)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> dis(-0.5, 0.5);

            float val = dis(gen);
            vec3.push_back(val);
        }
    Strength::SaveStrength(2, vec3);

    //초기 세팅
    //Setup();
    ////가중치를 통해 숫자 분류
    //for (int i = 0; i < 10; i++)
    //{
    //    for (int ii = 0; ii < 10; ii++)
    //    {
    //        string formatPath = format("../training/{:d}/{:d}.png", ii, i);
    //        const char* path = formatPath.c_str();

    //        classifyNumber(path);
    //        //역전파(traning상태일때만)
    //        cout << "정답 :" << ii << endl;
    //        back(ii);
    //    }
    //}
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
//순전파
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

//역전파
//살려줘..
void back(int answer)
{
    list<shared_ptr<Neuron>>::iterator iter1;
    int index = 0;
    for (iter1 = outputLayer.begin(); iter1 != outputLayer.end(); iter1++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter1;
        float errorRating;
        if (index == answer)
            errorRating = selectedNeuron -> value - 1;
        else
            errorRating = selectedNeuron->value;
        index++;

        

        list<shared_ptr<Relation>>::iterator iter2;
        for (iter2 = selectedNeuron->Backrelation->begin(); iter2 != selectedNeuron->Backrelation->end(); iter2++)
        {
            shared_ptr<Relation> selectedRelation = *iter2;
            float errorRating2 = errorRating * selectedRelation->strength;

            selectedRelation->ChangeStrength(errorRating2);
            list<shared_ptr<Relation>>::iterator iter3;
            for (iter3 = selectedRelation->item1->Backrelation->begin(); iter3 != selectedRelation->item1->Backrelation->end(); iter3++)
            {
                shared_ptr<Relation> selectedRelation = *iter3;
                float errorRating3 = errorRating2 * selectedRelation->strength;

                selectedRelation->ChangeStrength(errorRating3);
                list<shared_ptr<Relation>>::iterator iter4;
                for (iter4 = selectedRelation->item1->Backrelation->begin(); iter4 != selectedRelation->item1->Backrelation->end(); iter4++)
                {
                    shared_ptr<Relation> selectedRelation = *iter4;
                    float errorRating4 = errorRating3 * selectedRelation->strength;

                    selectedRelation->ChangeStrength(errorRating3);
                }
            }
        }

        vector<float> relationS = vector<float>();
        list<shared_ptr<Neuron>>::iterator iter1;
        for (iter1 = inputLayer.begin(); iter1 != inputLayer.end(); iter1++)
        {
            shared_ptr<Neuron> selectedNeuron = *iter1;
            list<shared_ptr<Relation>>::iterator iter2;
            for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
            {
                shared_ptr<Relation> selectedNeuron = *iter2;
                selectedNeuron->strength = selectedNeuron->changedStrength;
                relationS.push_back(selectedNeuron->strength);
            }
        }
        Strength::SaveStrength(0, relationS);

        relationS = vector<float>();
        for (iter1 = hiddenLayer1.begin(); iter1 != hiddenLayer1.end(); iter1++)
        {
            shared_ptr<Neuron> selectedNeuron = *iter1;
            list<shared_ptr<Relation>>::iterator iter2;
            for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
            {
                shared_ptr<Relation> selectedNeuron = *iter2;
                selectedNeuron->strength = selectedNeuron->changedStrength;
                relationS.push_back(selectedNeuron->strength);
            }
        }
        Strength::SaveStrength(1, relationS);

        relationS = vector<float>();
        for (iter1 = hiddenLayer2.begin(); iter1 != hiddenLayer2.end(); iter1++)
        {
            shared_ptr<Neuron> selectedNeuron = *iter1;
            list<shared_ptr<Relation>>::iterator iter2;
            for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
            {
                shared_ptr<Relation> selectedNeuron = *iter2;
                selectedNeuron->strength = selectedNeuron->changedStrength;
                relationS.push_back(selectedNeuron->strength);
            }
        }
        Strength::SaveStrength(2, relationS);

    }
}