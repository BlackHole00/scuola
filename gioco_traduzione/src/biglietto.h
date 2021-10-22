#pragma once
#include <iostream>

using namespace std;

class Biglietto {
    friend istream& operator>>(istream&, Biglietto&);

private:
    string vocaboloPrincipale;
    string vocaboloStaniero;

public:
    Biglietto();
    Biglietto(string, char);
    Biglietto(string, string);

    string GetVocaboloPrincipale();
    string GetVocaboloStaniero();

    void SetVocaboloPrincipale(string);
    void SetVocaboloStaniero(string);
};