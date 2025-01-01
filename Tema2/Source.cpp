#include "AFD.h"

int main()
{
	AFD afd;
	afd.Citire("./input.txt");
	char user_choice;
	std::string cuvant_introdus;
	do
	{
		std::cout << "Indroduceti un cuvant pentru testat:\n";
		std::cin >> cuvant_introdus;
		afd.VerificareCuvant(cuvant_introdus);
		do
		{
			std::cout << "Doriti sa introduceti alt cuvant ? [Y/N]: ";
			std::cin >> user_choice;
		} 
		while (user_choice != 'Y' && user_choice != 'N');
	} 
	while (user_choice == 'Y');

	return 0;
}