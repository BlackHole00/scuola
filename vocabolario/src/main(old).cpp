//  Esercizio: Vocabolario
//  Studente: Viciguerra Francesco
//  Classe: 4AIA

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int VEC_LUNG = 150;
const int ERR_VOCABOLO_ESISTENTE = -2;
const int ERR_VETTORE_PIENO = -1;
const int ERR_FILE_NON_APERTO = -1;
const int ERR_FORMATO_NON_VALIDO = -2;
const int ERR_VOCABOLI_NON_IN_ORDINE = -3;

struct Vocabolo {
    string vocaboloLinguaPrimaria;
    string vocaboloLinguaSecondaria;
};

string CinGetLine();
char Menu();
Vocabolo ChiediVocabolo(string, string);
string ChiediParola(string);
int InserisciVocabolo(Vocabolo[], int&, Vocabolo);
bool TrovaPosizioneOttimale(int&, Vocabolo[], int, string);
int TrovaVocabolo(Vocabolo[], int, string);
bool RimuoviVocabolo(Vocabolo[], int&, string);
bool ModificaVocabolo(Vocabolo[], int, Vocabolo);
void VisualizzaVocabolario(Vocabolo[], int);
bool SalvaVocabolario(Vocabolo[], int, string);
int CaricaVocabolario(Vocabolo[], int&, string);

int main() {
    Vocabolo vecVocaboli[VEC_LUNG];
    int lung = 0;

    string nomeLinguaPrimaria, nomeLinguaSecondaria;

    cout << "Inserire il nome della lingua originale: ";
    nomeLinguaPrimaria = CinGetLine();
    cout << "Inserire il nome della lingua straniera: ";
    nomeLinguaSecondaria = CinGetLine();

    char risposta;
    do {
        risposta = Menu();

        switch(risposta) {
            case '1': {
                int res = InserisciVocabolo(vecVocaboli, lung, ChiediVocabolo(nomeLinguaPrimaria, nomeLinguaSecondaria));
                switch(res) {
                    case ERR_VETTORE_PIENO: {
                        cout << "Il dizionario e' pieno. Eliminare un vocabolo prima di poter inserirne un altro!" << endl;
                        break;
                    }
                    case ERR_VOCABOLO_ESISTENTE: {
                        cout << "Il vocabolo e' gia' stato inserito. Per modificarlo utilizzare la voce 'Modifica vocabolo' dal menu!" << endl;
                        break;
                    }
                    default: {
                        cout << "Vocabolo inserito senza problemi!" << endl;
                    }
                }

                break;
            }
            case '2': {
                if (!RimuoviVocabolo(vecVocaboli, lung, ChiediParola(nomeLinguaPrimaria))) {
                    cout << "Il vocabolo specificato non e'esistente!" << endl;
                } else {
                    cout << "Vocabolo rimosso senza problemi!" << endl;
                }

                break;
            }
            case '3': {
                Vocabolo vocabolo;

                cout << "Inserire la parola in " << nomeLinguaPrimaria << " di cui si vuole modificare la traduzione: ";
                vocabolo.vocaboloLinguaPrimaria = CinGetLine();
                vocabolo.vocaboloLinguaSecondaria = ChiediParola(nomeLinguaSecondaria);

                if (!ModificaVocabolo(vecVocaboli, lung, vocabolo)) {
                    cout << "Il vocabolo specificato non e'esistente!" << endl;
                } else {
                    cout << "Vocabolo modificato senza problemi!" << endl;
                }

                break;
            }
            case '4': {
                VisualizzaVocabolario(vecVocaboli, lung);
                break;
            }
            case '5': {
                string nomeFile;
                cout << "Inserire il percorso del file sul quale si vuole salvare il vocabolario: ";
                cin >> nomeFile;

                if (!SalvaVocabolario(vecVocaboli, lung, nomeFile)) {
                    cout << "Non e' stato possibile salvare il vocabolario!" << endl;
                } else {
                    cout << "Vocabolario salvato con successo!" << endl;
                }

                break;
            }
            case '6': {
                string nomeFile;
                cout << "Inserire il percorso del file sul quale si vuole salvare il vocabolario: ";
                cin >> nomeFile;

                int res = CaricaVocabolario(vecVocaboli, lung, nomeFile);
                switch(res) {
                    case ERR_FILE_NON_APERTO: {
                        cout << "Non e' stato possibile caricare il vocabolario: non e' stato possibile aprire il file!" << endl;
                        break;
                    }
                    case ERR_FORMATO_NON_VALIDO: {
                        cout << "Non e' stato possibile caricare il vocabolario: Formato non valido!" << endl;
                        break;
                    }
                    case ERR_VOCABOLI_NON_IN_ORDINE: {
                        cout << "Non e' stato possibile caricare il vocabolario: I vocaboli non sono in ordine!" << endl;
                        break;
                    }
                    default: {
                        cout << "Vocabolario caricato con successo!" << endl;
                    }
                }

                break;
            }
            case '0': {
                cout << "Uscita!" << endl;
                break;
            }
            default: {
                cout << "Risposta non valida!!!" << endl;
                break;
            }
        }
    } while(risposta != '0');

    return 0;
}

char Menu() {
    cout << endl << "--- VOCABOLARIO ---" << endl;
    cout << "\t[1] Inserisci vocabolo" << endl;
    cout << "\t[2] Rimuovi vocabolo" << endl;
    cout << "\t[3] Modifica vocabolo" << endl;
    cout << "\t[4] Visualizza vocabolario" << endl;
    cout << "\t[5] Salva vocabolario su file" << endl;
    cout << "\t[6] Carica vocabolario da file" << endl;
    cout << "\t[0] Esci" << endl;
    cout << endl << "Risposta: ";

    char risposta;
    cin >> risposta;

    return risposta;
}

Vocabolo ChiediVocabolo(string nomeLinguaPrimaria, string nomeLinguaSecondaria) {
    Vocabolo vocabolo;

    vocabolo.vocaboloLinguaPrimaria = ChiediParola(nomeLinguaPrimaria);
    vocabolo.vocaboloLinguaSecondaria = ChiediParola(nomeLinguaSecondaria);

    return vocabolo;
}

string ChiediParola(string nomeLingua) {
    string parola;

    bool ok;
    do {
        cout << "Inserire il vocabolo in " << nomeLingua << ": ";
        parola = CinGetLine();

        ok = (parola.find('|') == -1);

        if (!ok) {
            cout << "Il vocabolo non puo' contenere il carattere '|' !" << endl;
        }
    } while(!ok);

    return parola;
}

int InserisciVocabolo(Vocabolo vecVocaboli[], int& lung, Vocabolo vocabolo) {
    if (lung >= VEC_LUNG) {
        return ERR_VETTORE_PIENO;
    }

    int pos;
    if (TrovaPosizioneOttimale(pos, vecVocaboli, lung, vocabolo.vocaboloLinguaPrimaria)) {
        return ERR_VOCABOLO_ESISTENTE;
    }
    cout << pos;


    for (int i = lung; i > pos; i--) {
        vecVocaboli[i] = vecVocaboli[i - 1];
    }
    vecVocaboli[pos] = vocabolo;
    lung ++;

    return 0;
}

int TrovaVocabolo(Vocabolo vecVocaboli[], int lung, string vocaboloLinguaPrimaria) {
    int sup = lung - 1;
    int inf = 0;
    int center;

    while (inf <= sup) {
        center = (sup + inf) / 2;

        if (vecVocaboli[center].vocaboloLinguaPrimaria == vocaboloLinguaPrimaria) {
            return center;
        }
        if (vecVocaboli[center].vocaboloLinguaPrimaria > vocaboloLinguaPrimaria) {
            sup = center - 1;
        } else if (vecVocaboli[center].vocaboloLinguaPrimaria < vocaboloLinguaPrimaria) {
            inf = center + 1;
        }
    }

    return -1;
}

bool RimuoviVocabolo(Vocabolo vecVocaboli[], int& lung, string vocaboloLinguaPrimaria) {
    int pos = TrovaVocabolo(vecVocaboli, lung, vocaboloLinguaPrimaria);
    if (pos == -1) {
        return false;
    }

    for (int i = pos; i < lung - 1; i++) {
        vecVocaboli[i] = vecVocaboli[i + 1];
    }
    lung--;

    return true;
}

bool ModificaVocabolo(Vocabolo vecVocaboli[], int lung, Vocabolo vocabolo) {
    //  La variabile vocabolo è utilizzata per trovare la posizione del vocabolo (attraverso
    //  vocabolo.vocaboloLinguaPrimaria) e per settare il nuovo valore alla posizione trovata
    //  (attraverso vocabolo.vocaboloLinguaSecondaria)

    int pos = TrovaVocabolo(vecVocaboli, lung, vocabolo.vocaboloLinguaPrimaria);
    if (pos == -1) {
        return false;
    }

    vecVocaboli[pos].vocaboloLinguaSecondaria = vocabolo.vocaboloLinguaSecondaria;

    return true;
}

bool TrovaPosizioneOttimale(int& pos, Vocabolo vecVocaboli[], int lung, string vocaboloLinguaPrimaria) {
    //  Settaggio sentinella per ricerca.
    vecVocaboli[lung].vocaboloLinguaPrimaria = vocaboloLinguaPrimaria;

    //  Scansionamento vettore.
    int i = 0;
    while(vecVocaboli[i].vocaboloLinguaPrimaria < vocaboloLinguaPrimaria) {
        i++;
    }

    //  Se la posizione ottimale trovata è uguale alla parola da inserire, ma non siamo alla fine del vettore (non è
    //  stata trovata la sentinella) vuol dire che la parola è stata già precedentemente inserita. Il valore ritornato
    //  è true (valore duplicato).
    if (vecVocaboli[i].vocaboloLinguaPrimaria == vocaboloLinguaPrimaria && i != lung) {
        return true;
    }

    //  Settaggio posizione e ritorno false (valore non duplicato)
    pos = i;
    return false;
}

void VisualizzaVocabolario(Vocabolo vecVocaboli[], int lung) {
    cout << "Numero vocaboli: " << lung << endl;

    for (int i = 0; i < lung; i++) {
        cout << vecVocaboli[i].vocaboloLinguaPrimaria << ": " << vecVocaboli[i].vocaboloLinguaSecondaria << endl;
    }
}

bool SalvaVocabolario(Vocabolo vecVocaboli[], int lung, string nomeFile) {
    fstream fileStream;
    fileStream.open(nomeFile.c_str(), ios::out);

    if (!fileStream.is_open()) {
        return false;
    }

    for(int i = 0; i < lung; i++) {
        fileStream << vecVocaboli[i].vocaboloLinguaPrimaria << "|" << vecVocaboli[i].vocaboloLinguaSecondaria << endl;
    }

    fileStream.close();

    return true;
}

int CaricaVocabolario(Vocabolo vecVocaboli[], int& lung, string nomeFile) {
    ifstream fileStream;
    fileStream.open(nomeFile.c_str(), ios::in);

    if (!fileStream.is_open()) {
        return ERR_FILE_NON_APERTO;
    }

    lung = 0;

    string linea;
    while(getline(fileStream, linea)) {
        int posCarateereDivisore = linea.find('|');
        if (posCarateereDivisore == -1) {
            lung = 0;

            return ERR_FORMATO_NON_VALIDO;
        }

        vecVocaboli[lung].vocaboloLinguaPrimaria = linea.substr(0, posCarateereDivisore);
        vecVocaboli[lung].vocaboloLinguaSecondaria = linea.substr(posCarateereDivisore + 1, linea.size());

        if (lung > 0 && vecVocaboli[lung].vocaboloLinguaPrimaria <= vecVocaboli[lung - 1].vocaboloLinguaPrimaria) {
            lung = 0;

            return ERR_VOCABOLI_NON_IN_ORDINE;
        }

        cout << vecVocaboli[lung].vocaboloLinguaPrimaria << " " << vecVocaboli[lung].vocaboloLinguaSecondaria << endl;

        lung++;
    }

    fileStream.close();

    return 0;
}

string CinGetLine() {
    string s;

    cin.sync();
    cin.clear();
    getline(cin, s);

    return s;
}
