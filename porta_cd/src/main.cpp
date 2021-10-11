#include <iostream>
#include "cd.h"
#include "porta_cd.h"

using namespace std;

char Menu();

int main() {
    int temp;
    cout << "Quanti cd deve il porta cd avere? ";
    cin >> temp;

    PortaCd pcd(temp);

    char risp;
    do {
        risp = Menu();

        switch (risp) {
            case '1': {
                cout << "Inserisci la posizione del cd: ";
                cin >> temp;

                Cd& cd = pcd.GetCd(temp);
                if (cd.GetNumeroBrani() != -1) {
                    cout << cd;
                } else {
                    cout << "Questo slot e' vuoto!!!" << endl;
                }

                break;
            }
            case '2': {
                Cd cd;
                cin >> cd;

                cout << "Inserisci la posizione del cd: ";
                cin >> temp;

                pcd.SetCd(cd, temp);

                break;
            }
            case '3': {
                cout << "Inserisci la posizione del cd da rimuovere: ";
                cin >> temp;

                pcd.KillCd(temp);

                break;
            }
            case '4': {
                cout << pcd;

                break;
            }
            case '5': {
                cout << "Todo!!!" << endl;

                break;
            }
            case '0': {
                break;
            }
            default: {
                cout << "Risposta non valida!!!" << endl;
            }
        }
    } while(risp != '0');

    return 0;
}

char Menu() {
    cout << "Menu:" << endl;
    cout << " 1: GetCD" << endl;
    cout << " 2: SetCD" << endl;
    cout << " 3: KillCD" << endl;
    cout << " 4: ViewAllCD" << endl;
    cout << " 5 [TODO]: CmpCD" << endl;
    cout << " 0: Exit" << endl;
    cout << "Risposta: ";

    char risp;
    cin >> risp;

    return risp;
}