#include <iostream>
#include "game.h"
#include "utils.h"

using namespace std;

char Menu();

int main() {
    Game game = Game("save.txt");

    if (!game.Load()) {
        cout << "Sembra che sia la prima volta che il programma venga avviato. Inserisci la prima domanda! " << endl;
        game.InsertFirstAnimal();
    }

    char resp;
    do {
        resp = Menu();

        switch (resp) {
            case '1': {
                if (game.Play()) {
                    if (AskQuestion("E' stato inserita una nuova domanda. Salvare? ") != 'n') {
                        game.Save();
                    }
                }

                break;
            }
            case '2': {
                if (!game.Save()) {
                    cout << "Non e' stato possibile salvare." << endl;
                }

                break;

                break;
            }
            case '3': {
                if (!game.Load()) {
                    cout << "Non e' stato possibile caricare." << endl;
                }

                break;
            }
            case '4': {
                game.Clear();

                break;
            }
            case '0': {
                cout << "Uscita!!!" << endl;

                break;
            }
            default: {
                cout << "Risposta non valida!!!" << endl;
                break;
            }
        }
    } while (resp != '0');

    //game.Load();

    return 0;
}

char Menu() {
    cout << "-----AKINATOR-----" << endl;
    cout << "[1]: Gioca" << endl;
    cout << "[2]: Salva" << endl;
    cout << "[3]: Carica" << endl;
    cout << "[4]: Pulisci" << endl;
    cout << "[0]: Esci" << endl;
    cout << "Risposta: ";

    char resp;
    cin >> resp;

    return resp;
}