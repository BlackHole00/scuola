#include <iostream>
#include "gioco.h"

using namespace std;

int main() {
    Gioco gioco;
    
    char risp;
    do {
        cout << "Vuoi selezionare i biglietti da file[F] o inserirli da tastiera[K]? [F/K] ";
        cin >> risp;

        risp = tolower(risp);
    } while(risp != 'f' && risp != 'k');

    if (risp == 'f') {
        string path;
        cout << "Inserisci il nome del file: ";
        getline(cin >> ws, path);

        if (!gioco.InizializzaGiocoDaFile(path)) {
            cout << "Errore durante inizializzazione da file!!!";
            return -1;
        }
    } else {
        gioco.InizializzaGioco();

        do {
            cout << "Vuoi salvare i biglietti su un file? [S/N] ";
            cin >> risp;

            risp = tolower(risp);
        } while(risp != 's' && risp != 'n');
        
        if (risp == 's') {
            string path;
            cout << "Inserisci il nome del file: ";
            getline(cin >> ws, path);

            if (!gioco.SalvaSuFile(path)) {
                cout << "Errore durante il salvataggio su file!!!";
                return -2;
            }
        }
    }

    int numErrori = gioco.Run();
    cout << "Hai fatto " << numErrori << " errori!!!" << endl;

    return 0;
}