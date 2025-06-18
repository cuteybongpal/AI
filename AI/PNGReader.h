#pragma once
#include <string>
#include <vector>

using namespace std;

class PNGReader
{
public:
	vector<float> ReadPNG(string path);
};

