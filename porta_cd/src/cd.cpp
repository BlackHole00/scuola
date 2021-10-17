#include "cd.h"
#include <sstream>

Cd::Cd() {
    titolo = "";
    autore = "";
    numeroBrani = -1;
    durata = -1;
}

Cd::Cd(string titolo, string autore, int numeroBrani, int durata) {
    this->titolo = titolo;
    this->autore = autore;
    this->numeroBrani = numeroBrani;
    this->durata = durata;
}

string Cd::GetTitolo() const {
    return titolo;
}

string Cd::GetAutore() const {
    return autore;
}

int Cd::GetNumeroBrani() const {
    return numeroBrani;
}

int Cd::GetDurata() const {
    return durata;
}

void Cd::SetTitolo(string titolo) {
    this->titolo = titolo;
}

void Cd::SetAutore(string autore) {
    this->autore = autore;
}

void Cd::SetNumeroBrani(int numeroBrani) {
    this->numeroBrani = numeroBrani;
}
    
void Cd::SetDurata(int durata) {
    this->durata = durata;
}

string Cd::ToString() const {
    stringstream ss;

    ss << "Cd " << titolo << " (by " << autore << ", " << numeroBrani << " brani, durata: " << durata << " secs)" << endl;

    return ss.str();
}

int Cd::CmpDurata(const Cd& other) const {
    return this->durata - other.GetDurata();
}

ostream& operator<<(ostream& os, const Cd& cd) {
    string str = cd.ToString();
    os << str;

    return os;
}

istream& operator>>(istream& is, Cd& cd) {
    cout << "Inserisci il titolo: ";
    is >> cd.titolo;
    cout << "Inserisci l'autore: ";
    is >> cd.autore;
    cout << "Inserisci il numero di brani: ";
    is >> cd.numeroBrani;
    cout << "Inserisci la durata in secondi: ";
    is >> cd.durata;
    
    return is;
}
