#include "AFN.h"
#include "AFD.h"

int main()
{
	AFN afn;
	AFD afd;
	afn.Citire("./input.txt");
	afd.AfisareAFD("./output.txt", afn);

	return 0;
}