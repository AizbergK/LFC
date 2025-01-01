#include "AFD.h"
#include "Delta.h"

void AFD::Citire(std::string path)
{
	std::ifstream input(path);

	std::string line, temp_str;
	std::getline(input, line);
	std::getline(input, line); // starile
	std::stringstream str_ipt{ line };
	while (str_ipt >> temp_str)
	{
		this->Stari.emplace_back(temp_str);
	}
	std::getline(input, line);
	str_ipt.clear();
	str_ipt.str(line);
	str_ipt >> this->StareInitiala;

	std::getline(input, line);
	std::getline(input, line); // starile finale
	str_ipt.clear();
	str_ipt.str(line);
	while (str_ipt >> temp_str)
	{
		this->StariFinale.emplace_back(temp_str);
	}

	std::getline(input, line);
	std::getline(input, line); // simbolurile
	str_ipt.clear();
	str_ipt.str(line);
	char ch;
	while (str_ipt >> ch)
	{
		Sigma.emplace_back(ch);
	}

	std::getline(input, line);
	while (std::getline(input, line)) // tranzitiile
	{
		str_ipt.clear();
		str_ipt.str(line);
		std::string stanga, dreapta;
		char simbol;
		str_ipt >> stanga >> simbol >> dreapta;
		DeltaClass tranzitie{ stanga, simbol, dreapta };
		Delta.emplace_back(tranzitie);
	}

	this->Validare();
	this->AfisareAFD();
}

void AFD::AfisareAFD()
{
	std::cout << "Starile automatului definit:\n{";
	for (auto& stare : this->Stari)
		std::cout << stare << ", ";
	std::cout << "\b\b}\n";
	std::cout << "Starea initiala a automatului definit: " << this->StareInitiala << '\n';
	std::cout << "Starile finale ale automatului definit:\n{";
	for (auto& stare : this->StariFinale)
		std::cout << stare << ", ";
	std::cout << "\b\b}\n";
	std::cout << "Simboluri ale automatului definit:\n{";
	for (auto& simb : this->Sigma)
		std::cout << simb << ", ";
	std::cout << "\b\b}\n";
	std::cout << "Tranzitiile automatului definit\n";
	for (auto& tranzitie : this->Delta)
	{
		std::cout << '{' << tranzitie.get_stanga() << ", " << tranzitie.get_simbol() << ", " << tranzitie.get_dreapta() << '}' << '\n';
	}
	std::cout << std::endl;
}
void AFD::Validare()
{
	if (std::find(this->Stari.begin(), this->Stari.end(), this->StareInitiala) == this->Stari.end())
	{
		std::cout << "Simbolul de start nu face parte din multimea simbolurilor\n";
		return;
	}
	for(auto stare : this->StariFinale)
		if(std::find(this->Stari.begin(), this->Stari.end(), this->StareInitiala) == this->Stari.end())
		{
			std::cout << "Un simbol din starile finale nu face parte din multimea simbolurilor\n";
			return;
		}
	for (auto tranzitie : this->Delta)
	{
		if (std::find(this->Sigma.begin(), this->Sigma.end(), tranzitie.get_simbol()) == this->Sigma.end())
		{
			std::cout << "Un simbol din tranzitie nu face parte din sigma\n";
		}
	}
}

void AFD::VerificareCuvant(std::string cuvant_de_verificat)
{
	std::string stare_actuala{ this->StareInitiala };
	for (auto ch : cuvant_de_verificat)
	{
		bool blocaj = true;
		for(auto stare : this->Delta)
		{
			if (stare.get_stanga() == stare_actuala && stare.get_simbol() == ch)
			{
				stare_actuala = stare.get_dreapta();
				blocaj = false;
				break;
			}
		}
		if(blocaj)	
		{
			std::cout << "Blocaj!\n";
			return;
		}
	}
	if (std::find(this->StariFinale.begin(), this->StariFinale.end(), stare_actuala) != this->StariFinale.end())
		std::cout << "Acceptat!\n";
	else
		std::cout << "Neacceptat!\n";
}