#include <iostream>

using namespace std;

const int VEC_LEN = 150;

struct Data {
    int giorno;
    int mese;
    int anno;
};

struct Atleta {
    int id;
    string nome;
    Data nascita;
    float tempo;
};

char Menu();
Atleta ChiediAtleta();
Data ChiediData();
int ChiediId();
int InserisciAtleta(Atleta[], int&, Atleta);
int TrovaAtletaById(Atleta[], int, int);
bool ImpostaTempoAtletaById(Atleta[], int, int, float);
bool ControllaTempi(Atleta[], int);
void RiordinaAtleti(Atleta[], int);
bool RimuoviAtleta(Atleta[], int&, int);
void ElencaAtletiByNome(Atleta[], int, string);
void ElencaAtleti(Atleta[], int);
template <class T>
inline void SwapVars(T&, T&);

int main() {
    Atleta vecAtleti[VEC_LEN];
    int lung;

    char res;
    do {
        res = Menu();

        switch(res) {
            case '1': {
                Atleta atl = ChiediAtleta();
                int res = InserisciAtleta(vecAtleti, lung, atl);
                switch (res) {
                    case -1: {
                        cout << "E' gia' presente un atleta con questo id!" << endl;
                        break;
                    }
                    case -2: {
                        cout << "E' stato reggiunto il massimo numero di atleti!" << endl;
                        break;
                    }
                    default: {
                        cout << "L'atleta e' stato inserito senza problemi!" << endl;
                        break;
                    }
                }
                
                break;
            }
            case '2': {
                int id = ChiediId();
                if (!RimuoviAtleta(vecAtleti, lung, id)) {
                    cout << "Non e' stato possibile trovare l'atleta specificato!" << endl;
                }

                break;
            }
            case '3': {
                float tempo;
                int id = ChiediId();

                cout << "Inserire il tempo dell'atleta: ";
                cin >> tempo;

                if (!ImpostaTempoAtletaById(vecAtleti, lung, id, tempo)) {
                    cout << "Non e' stato possibile trovare l'atleta specificato!" << endl;
                }

                break;
            }
            case '4': {
                if (!ControllaTempi(vecAtleti, lung)) {
                    char risp;
                    cout << "Non sono stati inseriti i tempi di tutti i giocatori. Continuare comunque? [s/n]: ";
                    cin >> risp;

                    risp = tolower(risp);

                    if (risp != 's' && risp != 'y') {
                        break;
                    }
                }

                RiordinaAtleti(vecAtleti, lung);

                break;
            }
            case '5': {
                ElencaAtleti(vecAtleti, lung);

                break;
            }
            case '6': {
                string nome;
                cout << "Inserire il nome dell'atleta: ";
                cin >> nome;

                ElencaAtletiByNome(vecAtleti, lung, nome);
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
    } while(res != '0');

    return 0;
}

char Menu() {
    cout << endl << "MENU:" << endl;
    cout << "\t[1] Inserisci Atleta" << endl;
    cout << "\t[2] Rimuovi Atleta" << endl;
    cout << "\t[3] Inserisci Tempo" << endl;
    cout << "\t[4] Ordina Elenco Per Tempo" << endl;
    cout << "\t[5] Visualizza Elenco" << endl;
    cout << "\t[6] Cerca Atleta Per Nome" << endl;
    cout << "\t[0] Esci" << endl;
    cout << "Risposta: ";

    char risposta;
    cin >> risposta;

    return risposta;
}

Atleta ChiediAtleta() {
    Atleta atl;
    
    cout << "Inserire il nome dell'atleta: ";
    cin >> atl.nome;
    cout << "Inserire l'id dell'atleta: ";
    cin >> atl.id;
    atl.nascita = ChiediData();

    atl.tempo = -1.0f;

    return atl;
}

Data ChiediData() {
    Data data;

    do {
        cout << "Inserire il giorno di nascita dell'atleta: ";
        cin >> data.giorno;
    } while(data.giorno < 1 || data.giorno > 31);
    do {
        cout << "Inserire il mese di nascita dell'atleta: ";
        cin >> data.mese;
    } while(data.mese < 1 || data.mese > 12);
    do {
        cout << "Inserire il anno di nascita dell'atleta: ";
        cin >> data.anno;
    } while(data.anno < 0);

    return data;
}

int ChiediId() {
    cout << "Inserire l'id dell'atleta: ";

    int id;
    cin >> id;

    return id;
}

int InserisciAtleta(Atleta vecAtleti[], int& lung, Atleta atl) {
    if (TrovaAtletaById(vecAtleti, lung, atl.id) != -1) {
        return -1;
    }
    if (lung == VEC_LEN - 2) {
        return -2;
    }

    vecAtleti[lung] = atl;
    lung++;

    return 0;
}

int TrovaAtletaById(Atleta vecAtleti[], int lung, int id) {
    vecAtleti[lung].id = id;

    int i = 0;
    while(vecAtleti[i].id != id) {
        i++;
    }

    if (i == lung) {
        return -1;
    }
    return i;
}

bool ImpostaTempoAtletaById(Atleta vecAtleti[], int lung, int id, float valore) {
    int pos = TrovaAtletaById(vecAtleti, lung, id);
    if (pos == -1) {
        return false;
    }

    vecAtleti[pos].tempo = valore;

    return true;
}

bool ControllaTempi(Atleta vecAtleti[], int lung) {
    vecAtleti[lung].tempo = -1.0f;

    int i = 0;
    while (vecAtleti[i].tempo >= 0.0f) {
        i++;
    }

    if (i != lung) {
        return false;
    }
    return true;
}

void RiordinaAtleti(Atleta vecAtleti[], int lung) {
    int sup = lung - 1;
    int us = sup;

    do {
        us = -1;

        for (int i = 0; i < sup; i++) {
            if (vecAtleti[i].tempo > vecAtleti[i + 1].tempo) {
                SwapVars<Atleta>(vecAtleti[i], vecAtleti[i + 1]);
                us = i;
            }
        }

        sup = us;
    } while(us != -1);
}

bool RimuoviAtleta(Atleta vecAtleti[], int& lung, int id) {
    int pos = TrovaAtletaById(vecAtleti, lung, id);
    if (pos == -1) {
        return false;
    }

    for (int i = pos; i < lung - 1; i++) {
        vecAtleti[i] = vecAtleti[i + 1];
    }
    lung--;

    return true;
}

void ElencaAtletiByNome(Atleta vecAtleti[], int lung, string nome) {
    for (int i = 0; i < lung; i++) {
        if (vecAtleti[i].nome == nome) {
            cout << "Trovato " << vecAtleti[i].nome << " nato il " << vecAtleti[i].nascita.giorno << "/" << vecAtleti[i].nascita.mese << "/" << vecAtleti[i].nascita.anno;
            if (vecAtleti[i].tempo >= 0.0f) {
                cout << " con tempo " << vecAtleti[i].tempo;
            }
            cout << " (Id: " << vecAtleti[i].id << ")" << endl;
        }
    }
}

void ElencaAtleti(Atleta vecAtleti[], int lung) {
    for (int i = 0; i < lung; i++) {
        cout << "Atleta " << i << ": " << vecAtleti[i].nome << " nato il " << vecAtleti[i].nascita.giorno << "/" << vecAtleti[i].nascita.mese << "/" << vecAtleti[i].nascita.anno;
            if (vecAtleti[i].tempo >= 0.0f) {
                cout << " con tempo " << vecAtleti[i].tempo;
            }
        cout << " (Id: " << vecAtleti[i].id << ")" << endl;
    }
}

template <class T>
inline void SwapVars(T& var1, T& var2) {
    T temp;
    temp = var1;
    var1 = var2;
    var2 = temp;
}
