#pragma once
#include <iostream>

using namespace std;

class Cd {
    friend ostream& operator<<(ostream&, const Cd&);
    friend istream& operator>>(istream&, Cd&);

private:
    string titolo;
    string autore;
    int numeroBrani;
    int durata; 

public:
    Cd();
    Cd(string, string, int, int);

    string GetTitolo() const;
    string GetAutore() const;
    int GetNumeroBrani() const;
    int GetDurata() const;

    void SetTitolo(string);
    void SetAutore(string);
    void SetNumeroBrani(int);
    void SetDurata(int);

    string ToString() const;

    /*  Potrebbe essere una funzione friend, ma credo che così sia più leggibile.   */
    int CmpDurata(const Cd&) const;
};