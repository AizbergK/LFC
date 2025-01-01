#include "AFD.h"
#include "AFN.h"
#include "Delta.h"
#include <unordered_map>
#include <map>

void AFD::AfisareAFD(std::string output, AFN &afn)
{
	this->Transformare(afn);
	std::ofstream opt{ output };
	opt << "M' = { {";
	for (int i{ 0 }; i != this->Stari.size() - 1; ++i)
		opt << this->Stari[i] << ", ";
	opt << this->Stari[this->Stari.size() - 1] << "}, {";

	for (int i{ 0 }; i != this->Sigma.size() - 1; ++i)
		opt << this->Sigma[i] << ", ";
	opt << this->Sigma[this->Sigma.size() - 1] << "}, ";

	opt << "Delta, ";

	opt << this->StareInitiala << ", {";

	for (int i{ 0 }; i != this->StariFinale.size() - 1; ++i)
		opt << this->StariFinale[i] << ", ";
	opt << this->StariFinale[this->StariFinale.size() - 1] << "} }\n";
	opt << "Delta:\n";
	for (auto& tranzitie : this->Delta)
	{
		opt << "\tDelta(" << tranzitie.get_stanga() << ", " << tranzitie.get_simbol() << ") = " << tranzitie.get_dreapta() << '\n';
	}
}

std::string AFD::get_nume_stare(std::vector<std::string> stare)
{
	std::sort(stare.begin(), stare.end());
	std::string stare_noua;
	for (auto sub_st : stare)
		stare_noua += sub_st;
	return stare_noua;
}

void AFD::Transformare(AFN &afn)
{
	std::vector<std::string> stari_temp{ afn.get_StareInitiala() };
	auto stari_afn{ afn.get_Stari() };
	auto sigma_afn{ afn.get_Sigma() };
	auto transf_afn{ afn.get_Delta() };
	std::unordered_map<std::string, std::unordered_map<char, std::vector<std::string>>> stari_legaturi;
	const std::string lmbd{ "!" };

	for (auto& stare : stari_afn)
	{
		for (auto& transf : transf_afn)
		{
			for (auto simb : sigma_afn)
			{
				if (transf.get_stanga() == stare && transf.get_simbol() == simb)
				{
					stari_legaturi[transf.get_stanga()][simb].emplace_back(transf.get_dreapta());
				}
			}
		}
	}

	std::unordered_map<std::string, std::map<char, std::vector<std::string>>> stari_noi_legaturi;
	std::vector<std::vector<std::string>> stari_noi;
	for (auto st : stari_afn)
		stari_noi.emplace_back(std::vector<std::string>{st});
	stari_noi.emplace_back(std::vector<std::string>{ lmbd });

	for (int i{ 0 }; i != stari_noi.size(); ++i)
	{
		auto stare{ stari_noi[i] };
		for (auto simb : sigma_afn)
		{
			std::string stare_noua{ get_nume_stare(stare) };

			for (auto& transf : transf_afn)
			{
				for(auto sub_st : stare)
				{
					if (transf.get_stanga() != sub_st || transf.get_simbol() != simb)
						continue;

					if (stari_legaturi[sub_st].find(simb) != stari_legaturi[sub_st].end())
					{
						if(std::find(stari_noi_legaturi[stare_noua][simb].begin(), stari_noi_legaturi[stare_noua][simb].end(), transf.get_dreapta()) == stari_noi_legaturi[stare_noua][simb].end())
							stari_noi_legaturi[stare_noua][simb].emplace_back(transf.get_dreapta());
					}
				}
			}

			if(stari_noi_legaturi[stare_noua][simb].size() > 0)
			{
				if (std::find(stari_noi.begin(), stari_noi.end(), stari_noi_legaturi[stare_noua][simb]) == stari_noi.end())
					stari_noi.emplace_back(stari_noi_legaturi[stare_noua][simb]);
			}
			else
			{
				stari_noi_legaturi[stare_noua][simb].emplace_back(lmbd);
			}
		}
	}

	for (int i{ 0 }; i != stari_noi.size(); ++i)
	{
		for (auto it{ stari_noi_legaturi[get_nume_stare(stari_noi[i])].begin() }; it != stari_noi_legaturi[get_nume_stare(stari_noi[i])].end(); ++it)
		{
			DeltaClass delta("q" + std::to_string(i), (*it).first, "q" + std::to_string(std::find(stari_noi.begin(), stari_noi.end(), (*it).second) - stari_noi.begin()));
			this->Delta.emplace_back(delta);
		}
	}
	for (int i{ 0 }; i != stari_noi.size(); ++i)
	{
		this->Stari.emplace_back("q" + std::to_string(i));
		if (stari_noi[i].size() == 1 && std::find(stari_noi[i].begin(), stari_noi[i].end(), afn.get_StareInitiala()) != stari_noi[i].end())
			this->StareInitiala = "q" + std::to_string(i);
		for(auto sf : afn.get_StariFinale())
			if (std::find(stari_noi[i].begin(), stari_noi[i].end(), sf) != stari_noi[i].end())
			{
				this->StariFinale.emplace_back("q" + std::to_string(i));
				break;
			}
	}
	this->Sigma = afn.get_Sigma();
}
