#include <iostream>
#include "Gramatica.h"

int main()
{
    //Consideram "*" ca fiind lambda
    Gramatica gramaticaCorecta1, gramaticaCorecta2,prodFaraVn, intersectieNevida, startNotVn, prodFaraStart, prodCuNotVnVt;

    intersectieNevida.Generare("./intersectienevida.txt");
    startNotVn.Generare("./startnotvn.txt");
    prodFaraVn.Generare("./prodfaravn.txt");
    prodFaraStart.Generare("./prodfarastart.txt");
    prodCuNotVnVt.Generare("./prodcunotvnvt.txt");
    gramaticaCorecta1.Generare("./input1.txt");
    gramaticaCorecta2.Generare("./input2.txt");

    return 0;
}