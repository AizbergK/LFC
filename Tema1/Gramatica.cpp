#include "Gramatica.h"
#include "Productie.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <filesystem>

void Gramatica::Citire(std::string path)
{
	std::ifstream file(path);
	std::filesystem::directory_entry entry{ path };
	if (!entry.exists())
	{
		throw std::runtime_error("Fisierul nu exista");
	}

	if (file.is_open())
	{
		int loopNumber;
		char symbol;
		std::string left, right;

		//Citire Vn
		file >> loopNumber;
		for (int idx = 0; idx < loopNumber; ++idx)
		{
			file >> symbol;
			this->Vn.insert(symbol);
		}

		//Citire Vt
		file >> loopNumber;
		for (int idx = 0; idx < loopNumber; ++idx)
		{
			file >> symbol;
			if (this->Vn.find(symbol) != Vn.end())
			{
				throw std::runtime_error("Simbolul din Vt \"" + std::string{ symbol } + "\" exista deja in Vn");
			}
			this->Vt.insert(symbol);
		}

		//Citire Start 
		file >> this->m_Start;
		if (this->Vn.find(this->m_Start[0]) == Vn.end())
		{
			throw std::runtime_error("Simbolul de start \"" + this->m_Start + "\" nu exista in Vn");
		}

		//Citire Productii 
		file >> loopNumber;
		for (int i = 0; i < loopNumber; ++i)
		{
			bool ContainsFromVn = false;
			file >> left >> right;
			this->Productii.push_back(Productie(left, right));
		}
	}
	else
	{
		throw std::runtime_error("Nu se poate deschide fisierul");
	}

}

void Gramatica::Verificare()
{
	//Verificare intersectie Vn Vt
	for (auto &symb : this->Vt)
	{
		if (this->Vn.find(symb) != Vn.end())
		{
			throw std::runtime_error("Simbolul din Vt \"" + std::string{ symb } + "\" exista deja in Vn");
		}
	}

	//Verificare simbol Start
	if (this->Vn.find(this->m_Start[0]) == Vn.end())
	{
		throw std::runtime_error("Simbolul de start \"" + this->m_Start + "\" nu exista in Vn");
	}

	//Verificare productii
	bool containsStart = false;
	for (auto &prod : Productii)
	{
		bool ContainsFromVn = false;

		for (char ch : prod.get_left()) {
			if (this->Vn.find(ch) != Vn.end()) ContainsFromVn = true;
			if (this->Vn.find(ch) == Vn.end() && this->Vt.find(ch) == Vt.end())
			{
				throw std::runtime_error("Simbolul \"" + std::string{ ch } + "\" nu exista in Vn");
			}
		}
		if (!ContainsFromVn)
		{
			throw std::runtime_error("\"" + prod.get_left() + "\"(stanga) nu contine un simbol din Vn");
		}
		for (char ch : prod.get_right())
		{
			if (this->Vn.find(ch) == Vn.end() && this->Vt.find(ch) == Vt.end() && ch != '*')
			{
				throw std::runtime_error("Simbolul \"" + std::string{ ch } + "\" din \"" + prod.get_right() + "\" nu exista in Vn sau Vt");
			}
		}
		if (prod.get_left().find(this->m_Start) != std::string::npos) containsStart = true;
	}
	if (!containsStart) throw std::runtime_error("Nicio productie nu contine simbolul de start \"" + this->m_Start + "\"");
}

void Gramatica::AfisareGramatica()
{
	std::cout << " Vn: {";

	for (auto& temp : this->Vn)
		std::cout << temp << ", ";
	std::cout <<"\b\b}" << std::endl;

	std::cout << " Vt: {";
	for (auto& temp : this->Vt)
		std::cout << temp << ", ";
	std::cout << "\b\b}" << std::endl;

	std::cout << "Simbol start: ";
	std::cout << this->m_Start;
	std::cout << std::endl;

	std::cout << "Productiile:" << std::endl;
	for(int i = 0; i < Productii.size(); ++i)
		std::cout << " (" << i + 1 << ")" << Productii[i].get_left() << "->" << Productii[i].get_right() << std::endl;
	std::cout << std::endl;
}

void Gramatica::GenerareCuvant(bool showSteps)
{
	std::stringstream outputMsg;
	std::string word = this->m_Start;
	outputMsg << word << "-";
	bool prodPossible;

	do 
	{
		prodPossible = false;
		std::vector<int> possibleProd;
		for (int i = 0; i < Productii.size(); ++i)
		{
			if (word.find(Productii[i].get_left()) != std::string::npos)
			{
				prodPossible = true;
				possibleProd.push_back(i);
			}
		}
		if (!prodPossible) break;

		std::random_device generator;
		std::uniform_int_distribution<int> randProduction(0, possibleProd.size() - 1);
		int randProdRes = randProduction(generator);

		const std::string leftProd = Productii[possibleProd[randProdRes]].get_left();
		const std::string rightProd = Productii[possibleProd[randProdRes]].get_right();

		std::string temp = word;
		std::vector<int> possiblePos;
		while (temp.find(leftProd) != std::string::npos)
		{
			int pos = temp.find(leftProd);
			possiblePos.push_back(pos);
			temp = temp.substr(pos + leftProd.size());
		}

		std::uniform_int_distribution<> randPosition(0, possiblePos.size() - 1);
		int	randPosRes = randPosition(generator);
		if (rightProd == "*")
		{
			word.replace(possiblePos[randPosRes], leftProd.size(), "");
		}
		else
		{
			word.replace(possiblePos[randPosRes], leftProd.size(), rightProd);
		}
		outputMsg << "(" << possibleProd[randProdRes] + 1 << ")" << ">" << word << "-";
		
	} 
	while (prodPossible);
	
	if (Cuvinte.find(word) == Cuvinte.end())
	{
		outputMsg << "\b ";
		std::cout << std::setw(3) << Cuvinte.size() + 1 << "): " << "[" << word << "] ";
		if (showSteps)
			std::cout << outputMsg.str();
		std::cout << std::endl;
		Cuvinte.insert(word);
	}
}



void Gramatica::Generare(std::string path, bool showsteps, bool inputCuvinte)
{
	int nrCuvinte = 10;
	try
	{
		this->Citire(path);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << " | from: " << path<< std::endl << std::endl;
		return;
	}
	catch (...) {
		std::cout << "Unknown exception | from: " << path << std::endl << std::endl;
		return;
	}

	try
	{
		this->Verificare();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << " | from: " << path << std::endl << std::endl;
		return;
	}
	catch (...) {
		std::cout << "Unknown exception | from: " << path << std::endl << std::endl;
		return;
	}

	std::cout << "gramatica corecta din \"" << path << "\" este alcatuita din: " << std::endl;
	this->AfisareGramatica();

	if (inputCuvinte)
	{
		std::cout << "Introduceti nr de cuvinte generate: ";
		std::cin >> nrCuvinte;
	}
	while (this->Cuvinte.size() < nrCuvinte)
		this->GenerareCuvant(showsteps);
	std::cout << std::endl;
}
