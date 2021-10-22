#include "biglietto.h"

Biglietto::Biglietto() {
    vocaboloPrincipale = "";
    vocaboloStaniero = ""; 
}

Biglietto::Biglietto(string linea, char carattereDivisore) {
    size_t posCarateereDivisore = linea.find(carattereDivisore);

    vocaboloPrincipale = linea.substr(0, posCarateereDivisore);
    vocaboloStaniero = linea.substr(posCarateereDivisore + 1, linea.size());
}

Biglietto::Biglietto(string vp, string vs) {
    vocaboloPrincipale = vp;
    vocaboloStaniero = vs;
}

string Biglietto::GetVocaboloPrincipale() {
    return vocaboloPrincipale;
}

string Biglietto::GetVocaboloStaniero() {
    return vocaboloStaniero;
}

void Biglietto::SetVocaboloPrincipale(string voc) {
    vocaboloPrincipale = voc;
}

void Biglietto::SetVocaboloStaniero(string voc) {
    vocaboloStaniero = voc;
}

istream& operator>>(istream& is, Biglietto& biglietto) {
    cout << "Inserisci il vocabolo principale: ";
    getline(cin >> ws, biglietto.vocaboloPrincipale);
    cout << "Inserisci il vocabolo straniero: ";
    getline(cin >> ws, biglietto.vocaboloStaniero);

    return is;
}