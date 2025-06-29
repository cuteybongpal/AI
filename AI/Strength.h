#pragma once
#include <vector>
#include <fstream>
#include <ostream>
#include <istream>
#include <iostream>
#include <sstream>

using namespace std;

//진짜 개같이 어렵네
//이딴 거 만든놈은 brainfuck으로 32시간동안 코딩 형벌을 받아야 함ㄹㅇ
namespace Strength {
    const string path = "../strengths/Relation";

    vector<float> LoadStrength(int layerIndex)
    {
        string filepath = path + to_string(layerIndex) + "/str.txt";
        ifstream infile(filepath);

        if (!infile) {
            cout << "ㅈ댐 ㅋㅋ";
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
        //todo : 학습 후 바뀐 가중치를 바꾸기
        
        string filepath = path + to_string(layerIndex) + "/str.txt";
        ofstream outfile(filepath);

        for (int i = 0; i < relations.size(); i++)
        {
            outfile << relations[i].strength << ',';
        }
        outfile.close();
    }
}