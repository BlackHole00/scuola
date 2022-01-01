#include "utils.h"

#include <iostream>

char AskQuestion(string string) {
    char resp;

    bool ok = false;
    do {
        cout << string << " [s/n] ";
        cin >> resp;

        resp = tolower(resp);

        ok = (resp == 'y' || resp == 's' || resp == 'n');
        if (!ok) {
            cout << "Risposta non valida!!!" << endl;
        }
    } while (!ok);

    return resp;
}