#include "ADF.h"

int main()
{
	AFD afd;
	afd.Citire("./input.txt");
	char user_choice = 'Y';
	std::string cuvant_introdus;
	while (user_choice == 'Y')
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
	return 0;
}