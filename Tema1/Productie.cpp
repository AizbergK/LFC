#include "Productie.h"

Productie::Productie(std::string left, std::string right) : m_left{ left }, m_right{ right } {}

std::string Productie::get_left() { return this->m_left; }
std::string Productie::get_right() { return this->m_right; }
