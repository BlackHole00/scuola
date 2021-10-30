#include "gioco.h"
#include <fstream>
#include <string>

const char CARATTERE_DIVISORE = '|';

Gioco::Gioco() {
    numErrori = 0;
}

void Gioco::InizializzaGioco() {
    int num;
    Biglietto temp;

    biglietti = Queue<Biglietto>();
    numErrori = 0;

    cout << "Inserisci il nome della lingua principale: ";
    getline(cin >> ws, linguaPrincipale);
    cout << "Inserisci il nome della lingua straniera: ";
    getline(cin >> ws, linguaStraniera);

    cout << "Quanti biglietti vuoi inserire? ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        cin >> temp;

        biglietti.Enqueue(temp);
    }
}

void Gioco::AggiungiBiglietto() {
    Biglietto temp;
    cin >> temp;

    biglietti.Enqueue(temp);
}

void Gioco::ClearBiglietti() {
    biglietti.Empty();
}

int Gioco::NumBiglietti() {
    return biglietti.Length();
}

bool Gioco::InizializzaGiocoDaFile(string filePath) {
    fstream file;
    file.open(filePath.c_str(), ios::in);
    if (!file.is_open()) {
        return false;
    }

    biglietti = Queue<Biglietto>();
    numErrori = 0;

    getline(file, linguaPrincipale);
    getline(file, linguaStraniera);

    string line;
    while (getline(file, line)) {
        Biglietto temp(line, CARATTERE_DIVISORE);

        biglietti.Enqueue(temp);
    }

    file.close();

    return true;
}

int Gioco::Run() {
    while (!biglietti.IsEmpty()) {
        Biglietto temp = biglietti.DequeueReturn();
        string risp;

        cout << "Il vocabolo in " << linguaPrincipale << " e' " << temp.GetVocaboloPrincipale() << endl << "Qual'e' la traduzione in " << linguaStraniera << "? ";
        getline(cin >> ws, risp);

        if (risp == temp.GetVocaboloStaniero()) {
            cout << "CORRETTO!!!" << endl << endl;
        } else {
            cout << "ERRORE!!! La traduzione era " << temp.GetVocaboloStaniero() << "!" << endl << endl;
            numErrori++;
            biglietti.Enqueue(temp);
        }
    }

    return numErrori;
}

bool Gioco::SalvaSuFile(string filePath) {
    fstream file;
    file.open(filePath.c_str(), ios::out);

    if (!file.is_open()) {
        return false;
    }

    file << linguaPrincipale << endl;
    file << linguaStraniera << endl;

    int lung = biglietti.Length();
    for (int i = 0; i < lung; i++) {
        Biglietto temp = biglietti.DequeueReturn();

        file << temp.GetVocaboloPrincipale() << CARATTERE_DIVISORE << temp.GetVocaboloStaniero() << endl;

        biglietti.Enqueue(temp);
    }

    file.close();

    return true;
}