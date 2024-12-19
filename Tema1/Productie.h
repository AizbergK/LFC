#pragma once
#include<string>

class Productie
{
	std::string m_left, m_right;

public:
	Productie(std::string left, std::string right);
	std::string get_left();
	std::string get_right();
};

