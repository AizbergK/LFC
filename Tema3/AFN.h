#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include "Delta.h"

class AFN
{
	std::vector<std::string> Stari;
	std::vector<char> Sigma;
	std::vector<DeltaClass> Delta;
	std::string StareInitiala;
	std::vector<std::string> StariFinale;
	void AfisareAFN();
	void Validare();

public:
	void Citire(std::string path);
	std::vector<std::string> get_Stari();
	std::vector<char> get_Sigma();
	std::vector<DeltaClass> get_Delta();
	std::string get_StareInitiala();
	std::vector<std::string> get_StariFinale();
};