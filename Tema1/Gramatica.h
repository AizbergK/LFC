#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include "Productie.h"

class Gramatica
{
	std::string m_Start;
	std::unordered_set<char> Vn, Vt;
	std::vector<Productie> Productii;
	std::unordered_set<std::string> Cuvinte;
	void AfisareGramatica();
	void Citire(std::string path);
	void Verificare();
	void GenerareCuvant(bool showSteps);

public:
	void Generare(std::string path, bool showsteps = true, bool inputCuvinte = true);
};