#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>
#include "Delta.h"
#include "AFN.h"

class AFD
{
	AFN afn;
	std::vector<std::string> Stari;
	std::vector<char> Sigma;
	std::vector<DeltaClass> Delta;
	std::string StareInitiala;
	std::vector<std::string> StariFinale;
	void Transformare(AFN &afn);
	std::string get_nume_stare(std::vector<std::string>);

public:
	void AfisareAFD(std::string, AFN &afn);
};