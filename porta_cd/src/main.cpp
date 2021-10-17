#include <iostream>
#include <math.h>
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
                cout << "Inserisci la posizione del cd (1 - " << pcd.GetMaxSize() << "): ";
                cin >> temp;
                temp--;

                if (!pcd.CheckPos(temp)) {
                    cout << "Pos non valida!!! " << endl;
                    break;
                }
                Cd& cd = pcd.GetCd(temp);
                if (cd.GetNumeroBrani() != -1) {
                    cout << cd;
                }
                else {
                    cout << "Questo slot e' vuoto!!!" << endl;
                }

                break;
            }
            case '2': {
                Cd cd;
                cin >> cd;

                cout << "Inserisci la posizione del cd (1 - " << pcd.GetMaxSize() << "): ";
                cin >> temp;
                temp--;


                if (!pcd.CheckPos(temp)) {
                    cout << "Pos non valida!!! " << endl;
                    break;
                }
                pcd.SetCd(cd, temp);

                break;
            }
            case '3': {
                cout << "Inserisci la posizione del cd da rimuovere (1 - " << pcd.GetMaxSize() << "): ";
                cin >> temp;
                temp--;


                if (!pcd.CheckPos(temp)) {
                    cout << "Pos non valida!!! " << endl;
                    break;
                }
                pcd.KillCd(temp);

                break;
            }
            case '4': {
                cout << pcd;

                break;
            }
            case '5': {
                int temp2;

                cout << "Inserisci la posizione del cd 2 (1 - " << pcd.GetMaxSize() << "): ";
                cin >> temp;
                temp--;


                cout << "Inserisci la posizione del cd 1 (1 - " << pcd.GetMaxSize() << "): ";
                cin >> temp2;
                temp2--;


                if (!pcd.CheckPos(temp) || !pcd.CheckPos(temp2)) {
                    cout << "Pos non valida!!! " << endl;
                    break;
                }
                cout << "La differenza in durata e'" << abs(pcd.GetCd(temp).CmpDurata(pcd.GetCd(temp2))) << "secondi." << endl;

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
    cout << " 5: CmpCD" << endl;
    cout << " 0: Exit" << endl;
    cout << "Risposta: ";

    char risp;
    cin >> risp;

    return risp;
}