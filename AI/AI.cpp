#include <iostream>
#include "Neuron.h"
#include "Relation.h"
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <vector>

using namespace std;

list<shared_ptr<Neuron>> inputLayer = list<shared_ptr<Neuron>>();
list<shared_ptr<Neuron>> hiddenLayer1 = list<shared_ptr<Neuron>>();
list<shared_ptr<Neuron>> hiddenLayer2 = list<shared_ptr<Neuron>>();
list<shared_ptr<Neuron>> outputLayer = list<shared_ptr<Neuron>>();

list<Relation> relations1 = list<Relation>();
list<Relation> relations2 = list<Relation>();
list<Relation> relations3 = list<Relation>();

int main()
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

    for (iter1 = inputLayer.begin(); iter1 != inputLayer.end(); iter1++)
    {
        list<shared_ptr<Neuron>>::iterator iter2;

        for (iter2 = hiddenLayer1.begin(); iter2 != hiddenLayer1.end(); iter2++)
            relations1.push_back(Relation(*iter1, *iter2));
    }


    for (iter1 = hiddenLayer1.begin(); iter1 != hiddenLayer1.end(); iter1++)
    {
        list<shared_ptr<Neuron>>::iterator iter2;

        for (iter2 = hiddenLayer2.begin(); iter2 != hiddenLayer2.end(); iter2++)
            relations2.push_back(Relation(*iter1, *iter2));
    }

    for (iter1 = hiddenLayer2.begin(); iter1 != hiddenLayer2.end(); iter1++)
    {
        list<shared_ptr<Neuron>>::iterator iter2;

        for (iter2 = outputLayer.begin(); iter2 != outputLayer.end(); iter2++)
            relations3.push_back(Relation(*iter1, *iter2));
    }
}

// 고민점 : 아예 이 함수를 Relation 클래스에 포함할까 고민중임
vector<float> LoadStrength(int layerIndex, int relationIndex)
{
    //todo : 저장된 가중치 가져오기
    // 가중치는 strengths > Layer? <- 인덱스 번호 안에 있음   
}

void SaveStrength(int layerIndex, int relationIndex) 
{
    //todo : 학습 후 바뀐 가중치를 바꾸기
}
// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
