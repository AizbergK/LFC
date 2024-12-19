#include "Delta.h"

DeltaClass::DeltaClass(std::string stanga, char simbol, std::string dreapta) : m_stanga{ stanga }, m_simbol{ simbol }, m_dreapta{ dreapta } {}

std::string DeltaClass::get_stanga() { return this->m_stanga; }
std::string DeltaClass::get_dreapta() { return this->m_dreapta; }
char DeltaClass::get_simbol() { return this->m_simbol; }