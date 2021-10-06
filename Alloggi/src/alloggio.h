#pragma once
#include <iostream>

using namespace std;

class Alloggio {
    friend ostream& operator<<(ostream&, const Alloggio&);

private:
    int codice;
    float estensione;
    float costoMetroQuadro;
    float percentualeTasse;
    float estensioneCalpestabile;

public:
    Alloggio();
    Alloggio(int, float, float, float, float);

    float GetEstensioneCalpestabile();
    float GetPercentualeTasse();
    float CalcolaCostoTotaleSenzaTasse();
    float CalcolaCostoTotaleConTasse();
};