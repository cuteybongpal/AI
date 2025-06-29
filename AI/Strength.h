#pragma once
#include <vector>
#include <fstream>
#include <ostream>
#include <istream>
#include <iostream>
#include <sstream>

using namespace std;

//��¥ ������ ��Ƴ�
//�̵� �� ������� brainfuck���� 32�ð����� �ڵ� ������ �޾ƾ� �Ԥ���
namespace Strength {
    const string path = "../strengths/Relation";

    vector<float> LoadStrength(int layerIndex)
    {
        string filepath = path + to_string(layerIndex) + "/str.txt";
        ifstream infile(filepath);

        if (!infile) {
            cout << "���� ����";
        }
         
        stringstream buffer;
        buffer << infile.rdbuf();
        string content = buffer.str();

        istringstream ss(content);
        string temp;
        vector<float> vec = vector<float>();

        while (getline(ss, temp, ','))
        {
            char* errPtr;
            vec.push_back(strtof(temp.c_str(), &errPtr));
        }
        return vec;
    }

    void SaveStrength(int layerIndex, vector<Relation> relations)
    {
        //todo : �н� �� �ٲ� ����ġ�� �ٲٱ�
        
        string filepath = path + to_string(layerIndex) + "/str.txt";
        ofstream outfile(filepath);

        for (int i = 0; i < relations.size(); i++)
        {
            outfile << relations[i].strength << ',';
        }
        outfile.close();
    }
}