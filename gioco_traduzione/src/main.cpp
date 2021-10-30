#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "gioco.h"
#include "score.h"

using namespace std;

const string SAVE_PATH = "save.txt";
const string PASSWD_PATH = "passwd.txt";
const string SCORES_PATH = "scores.txt";
const int DIM = 5;

void PrimaConf();
string ReadPassword();
void ReadScores(Score[]);
void SaveScores(Score[]);
void CheckHighScore(Score[], int);
char Menu();
char AdmMenu();

int main() {
    Gioco gioco;
    Score scores[DIM];

    string passwd;
    PrimaConf();
    passwd = ReadPassword();
    ReadScores(scores);

    char risp;
    do {
        risp = Menu();
        gioco.InizializzaGiocoDaFile(SAVE_PATH);

        switch (risp) {
            case '1': {
                string temp;

                cout << "Inserisci la password:";
                getline(cin >> ws, temp);

                if (temp == passwd) {
                    char risp2;

                    do {
                        risp2 = AdmMenu();

                        switch (risp2)
                        {
                            case '1': {
                                gioco.ClearBiglietti();
                                break;
                            }
                            case '2': {
                                gioco.AggiungiBiglietto();
                                break;
                            }
                            case '3': {
                                gioco.InizializzaGioco();
                                break;
                            }
                            case '4': {
                                for (int i = 0; i < DIM; i++) {
                                    scores[i] = Score();
                                }

                                break;
                            }
                            case '0': {
                                break;
                            }
                            default: {
                                cout << "Risposta non valida!!!" << endl;
                                break;
                            }
                        }
                    } while (risp2 != '0');

                    gioco.SalvaSuFile(SAVE_PATH);
                }
                else {
                    cout << "Password errata" << endl;
                }

                break;
            }
            case '2': {
                int numErrori = gioco.Run();
                cout << "Hai fatto " << numErrori << " errori!!!" << endl;

                CheckHighScore(scores, numErrori);

                break;
            }
            case '3': {
                cout << "HIGH SCORES:" << endl;
                for (int i = 0; i < 5; i++) {
                    if (scores[i].IsValid()) {
                        cout << scores[i].GetName() << ": " << scores[i].GetScore() << endl;
                    }
                }

                break;
            }
            case '0': {
                break;
            }
            default: {
                cout << "Scelta errata!!!" << endl;
            }
        }
    } while (risp != '0');

    SaveScores(scores);

    return 0;
}

char Menu() {
    cout << endl << "MENU:" << endl;
    cout << "\t1: Amministrazione" << endl;
    cout << "\t2: Gioco" << endl;
    cout << "\t3: Classifica" << endl;
    cout << "\t0: Esci" << endl << endl;
    cout << "Risposta: ";

    char temp;
    cin >> temp;

    return temp;
}

char AdmMenu() {
    cout << endl << "MENU AMMINISTAZIONE:" << endl;
    cout << "\t1: Rimuovi Carte" << endl;
    cout << "\t2: Aggiungi Carta" << endl;
    cout << "\t3: Crea Mazzo da zero" << endl;
    cout << "\t4: Cancella Classifica" << endl;
    cout << "\t0: Esci" << endl;
    cout << "Risposta: ";

    char temp;
    cin >> temp;

    return temp;
}

void PrimaConf() {
    fstream fs;
    fs.open(PASSWD_PATH.c_str(), ios::in);

    if (fs.is_open()) {
        fs.close();

        //  Non prima configurazione.
        return;
    }

    fs.close();
    fs.open(PASSWD_PATH.c_str(), ios::out);

    string passwd;
    cout << "PRIMA CONFIGURAZIONE" << endl;
    cout << "Inserisci la password di amministrazione." << endl;
    getline(cin >> ws, passwd);

    fs << passwd << endl;

    fs.close();

    fs.open(SAVE_PATH.c_str(), ios::in);    fs.close();
    fs.open(SCORES_PATH.c_str(), ios::in);  fs.close();
}

string ReadPassword() {
    string temp = "";

    fstream fs;
    fs.open(PASSWD_PATH.c_str(), ios::in);
    if (fs.is_open()) {
        getline(fs, temp);
    }

    fs.close();

    return temp;
}

void ReadScores(Score vecScores[]) {
    fstream fs;
    fs.open(SCORES_PATH.c_str(), ios::in);

    for (int i = 0; i < DIM; i++) {
        vecScores[i] = Score();
    }

    int i = 0;

    if (fs.is_open()) {
        string temp;
        while (getline(fs, temp)) {
            stringstream ss(temp);

            string user;
            int score;
            ss >> user;
            ss >> score;

            vecScores[i] = Score(user, score);

            i++;
        }
    }

    fs.close();
}

void SaveScores(Score vecScores[]) {
    fstream fs;
    fs.open(SCORES_PATH.c_str(), ios::out);

    if (fs.is_open()) {
        for (int i = 0; i < 5; i++) {
            if (vecScores[i].IsValid()) {
                fs << vecScores[i].GetName() << " " << vecScores[i].GetScore() << endl;
            }
        }
    }

    fs.close();
}

void CheckHighScore(Score vecScores[], int score) {
    int i = 0;
    while (vecScores[i] < score && i < DIM) {
        i++;
    }

    cout << i;

    if (i < DIM) {
        for (int j = DIM - 2; j >= i; j--) {
            vecScores[j + 1] = vecScores[j];
        }

        string tmp;
        cout << "HIGH SCORE!!!" << endl << "Inserisci il tuo nome : ";
        cin >> tmp;

        vecScores[i] = Score(tmp, score);
    }
}