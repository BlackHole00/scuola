#pragma once
#include <iostream>

using namespace std;

//  Classe biglietto
class Biglietto {
    friend istream& operator>>(istream&, Biglietto&);

private:
    string vocaboloPrincipale;
    string vocaboloStaniero;

public:
    Biglietto();
    //  Costruttore utilizzato per una linea letta da file con un carattere divisore al suo interno
    Biglietto(string, char);
    Biglietto(string, string);

    string GetVocaboloPrincipale();
    string GetVocaboloStaniero();

    void SetVocaboloPrincipale(string);
    void SetVocaboloStaniero(string);
};