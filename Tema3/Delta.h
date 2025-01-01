#pragma once
#include <string>

class DeltaClass
{
	std::string m_stanga, m_dreapta;
	char m_simbol;

public:
	DeltaClass(std::string stanga, char simbol, std::string dreapta);
	std::string get_stanga();
	std::string get_dreapta();
	char get_simbol();
};

