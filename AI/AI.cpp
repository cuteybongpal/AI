
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
    //초기 세팅
    Setup();
    //가중치를 통해 숫자 분류
    string formatPath = format("../training/{:d}/{:d}.png", 2, 0);
    const char* path = formatPath.c_str();

    classifyNumber(path);
    ////역전파(traning상태일때만)
    cout << "정답 :" << 0 << endl;

    
    //for (int filename = 0; filename < 10; filename++)
    //{
    //    for (int answer = 0; answer < 10; answer++)
    //    {
    //        string formatPath = format("../training/{:d}/{:d}.png", answer, filename);
    //        const char* path = formatPath.c_str();

    //        classifyNumber(path);
    //        //역전파(traning상태일때만)
    //        cout << "정답 :" << answer << endl;
    //        back(answer);
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
    vector<float> outputDelta = vector<float>();
    vector<float> hiddenLayer2Delta = vector<float>();
    vector<float> hiddenLayer1Delta = vector<float>();

    int index = 0;
    for (iter1 = outputLayer.begin(); iter1 != outputLayer.end(); iter1++)
    {
        if (index == answer)
            outputDelta.push_back(iter1->get() ->value - 1);
        else
            outputDelta.push_back(iter1->get()->value);
    }
    for (iter1 = hiddenLayer2.begin(); iter1 != hiddenLayer2.end(); iter1++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter1;
        float sum = 0;
        list<shared_ptr<Relation>>::iterator iter2;
        index = 0;
        //해당 뉴런이 출력 값에 준 영향을 모두 더하기
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
        {
            sum += iter2->get()->strength * outputDelta[index];
            index++;
        }

        float ErrorRating = sum * (1 - tanh(selectedNeuron->value) * tanh(selectedNeuron->value));
        hiddenLayer2Delta.push_back(ErrorRating);
        //ㄹㅇ 역전파 로직 굉장히 중요함.
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
        {
            shared_ptr<Relation> selectedRelation = *iter2;

            selectedRelation->ChangeStrength(ErrorRating);
        }
    }
    for (iter1 = hiddenLayer1.begin(); iter1 != hiddenLayer1.end(); iter1++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter1;
        float sum = 0;
        list<shared_ptr<Relation>>::iterator iter2;
        index = 0;
        //해당 뉴런이 출력 값에 준 영향을 모두 더하기
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
        {
            sum += iter2->get()->strength * hiddenLayer2Delta[index];
            index++;
        }

        float ErrorRating = sum * (1 - tanh(selectedNeuron->value) * tanh(selectedNeuron->value));
        hiddenLayer1Delta.push_back(ErrorRating);
        //ㄹㅇ 역전파 로직 굉장히 중요함.
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
        {
            shared_ptr<Relation> selectedRelation = *iter2;

            selectedRelation->ChangeStrength(ErrorRating);
        }
    }
    for (iter1 = inputLayer.begin(); iter1 != inputLayer.end(); iter1++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter1;
        float sum = 0;
        list<shared_ptr<Relation>>::iterator iter2;
        index = 0;
        //해당 뉴런이 출력 값에 준 영향을 모두 더하기
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
        {
            sum += iter2->get()->strength * hiddenLayer1Delta[index];
            index++;
        }

        float ErrorRating = sum * (1 - tanh(selectedNeuron->value) * tanh(selectedNeuron->value));
        //ㄹㅇ 역전파 로직 굉장히 중요함.
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
        {
            shared_ptr<Relation> selectedRelation = *iter2;

            selectedRelation->ChangeStrength(ErrorRating);
        }
    }
    vector<float> relationS = vector<float>();
    for (iter1 = inputLayer.begin(); iter1 != inputLayer.end(); iter1++)
    {
        shared_ptr<Neuron> selectedNeuron = *iter1;
        list<shared_ptr<Relation>>::iterator iter2;
        for (iter2 = selectedNeuron->Forrelation->begin(); iter2 != selectedNeuron->Forrelation->end(); iter2++)
        {
            shared_ptr<Relation> selectedNeuron = *iter2;
            selectedNeuron->strength = selectedNeuron->changedStrength;
            selectedNeuron->changedStrength = 0;
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
            selectedNeuron->changedStrength = 0;
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
            selectedNeuron->changedStrength = 0;
            relationS.push_back(selectedNeuron->strength);
        }
    }
    Strength::SaveStrength(2, relationS);

    for (iter1 = outputLayer.begin(); iter1 != outputLayer.end(); iter1++)
    {
        shared_ptr<Neuron> n = *iter1;

        n->prevalues->clear();
        n->value = 0;
    }
}