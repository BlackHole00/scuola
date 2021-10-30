#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include "stack.h"
using namespace std;

bool GeneraNotazione(const string&, string&, map<char, int>&);
bool CalcolaRis(const string&, int&, map<char, int>&);

int main() {
    string espr;

    map<char, int> mappaLettere;

    cout << "Inserisci la tua espressione: ";
    getline(cin >> ws, espr);

    string fin;
    if (GeneraNotazione(espr, fin, mappaLettere)) {
        cout << "Notazione polacca: " << fin << endl;
    }
    else {
        cout << "L'espressione e' sbagliata. Notazione polacca (probabilmente sbagliata): " << fin << endl; 
    }

    int res;
    if (CalcolaRis(fin, res, mappaLettere)) {
        cout << "Risultato: " << res << endl;
    }
    else {
        cout << "L'espressione e' sbagliata. Risultato (probabilmente sbagliato): " << res << endl;
    }
}

bool GeneraNotazione(const string& in, string& out, map<char, int>& mappaLettere) {
    out = "";
    Stack<char> s;

    bool ok = true;
    
    for (int i = 0; i < in.length(); i++) {
        switch (in[i]) {
            //  Se trovo un simbolo lo metto nello stack.
            case '+': case '-': case '*': case '/': {
                s.Push(in[i]);

                //  Immissione spazio per dividere i numeri.
                out += " ";
                break;
            }
            //  Se trovo il terminatore o ')' metto il simbolo
            case '\0': case ')': {
                if (!s.IsEmpty()) {
                    //  Immissione spazio per dividere i numeri.
                    out += " ";
                    out += s.PopReturn();
                }
                else {  //  Errore
                    ok = false;
                }
                break;
            }
            case ' ': case '(': {
                break;
            }
            default: {
                if (!isdigit(in[i])) {
                    out += in[i];

                    mappaLettere[in[i]] = 0;

                    break;
                }

                out += in[i];   //  Aggiunta numeri a stringa
                break;
            }
        }
    }

    if (!s.IsEmpty()) {
        ok = false;
    }
    while (!s.IsEmpty()) {
        out += s.PopReturn();   //  Mettiamo tutti i segni che rimangono
    }

    
    for (const auto& temp : mappaLettere) {
        cout << "Inserisci il valore di " << temp.first << ": ";
        cin >> mappaLettere[temp.first];
    }

    return ok;
}

bool CalcolaRis(const string& str, int& res, map<char, int>& mappaLettere)
{
    string tmp = "";
    Stack<int> s;

    res = 0;
    bool ok = true;

    for (int i = 0; i < str.length(); i++) {
        switch (str[i]) {
            //  Operazione +
            case '+': {
                if (s.Size() >= 2) {
                    int var1 = s.PopReturn();
                    int var2 = s.PopReturn();

                    int res = var2 + var1;
                    s.Push(res);
                } 
                else {  //  Errore
                    ok = false;
                }

                tmp = "";

                break;
            }
            //  Operatore '-'
            case '-': {
                if (s.Size() >= 2) {
                    int var1 = s.PopReturn();
                    int var2 = s.PopReturn();

                    int res = var2 - var1;
                    s.Push(res);
                }
                else {
                    ok = false;
                }

                tmp = "";

                break;
            }
            //  Operatore '*'
            case '*': {
                if (s.Size() >= 2) {
                    int var1 = s.PopReturn();
                    int var2 = s.PopReturn();

                    int res = var2 * var1;
                    s.Push(res);
                }
                else {
                    ok = false;
                }

                tmp = "";

                break;
            }
            //  Operatore '/'
            case '/': {
                if (s.Size() >= 2) {
                    int var1 = s.PopReturn();
                    int var2 = s.PopReturn();

                    int res = var2 / var1;
                    s.Push(res);
                }
                else {
                    ok = false;
                }

                tmp = "";

                break;
            }
            //  Trasformiamo temp in un numero e lo mettiamo nello stack.
            case ' ': {
                if (tmp.length() > 0) {
                    s.Push(atoi(tmp.c_str()));

                    tmp = "";
                }
                break;
            };
            //  Se abbiamo un numero lo aggiungiamo a temp
            default: {
                if (!isdigit(str[i])) {
                    s.Push(mappaLettere[str[i]]);

                    break;
                }

                tmp += str[i];
                break;
            }
        }
    }

    if (s.Size() > 0) {
        res = s.Top();
    }
    if (s.Size() > 1) {
        ok = false;
    }

    return ok;
}
