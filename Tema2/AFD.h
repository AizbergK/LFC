#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include "Delta.h"

class AFD
{
	std::vector<std::string> Stari;
	std::vector<char> Sigma;
	std::vector<DeltaClass> Delta;
	std::string StareInitiala;
	std::vector<std::string> StariFinale;
	void AfisareAFD();
	void Validare();

public:
	void Citire(std::string path);
	void VerificareCuvant(std::string cuvant_de_verificat);
};