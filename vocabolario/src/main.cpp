/*  Esercizio: Vocabolario
*   Studente: Viciguerra Francesco
*   Classe: 4AIA
* 
*   Note:
*   - il vettore � sempre ordinato: ogni singolo vocabolo viene inserito in ordine.
*   - i vocaboli non possono contenere il carattere divisore (default: '|'), perch� va in conflitto con il sistema di
*       salvataggio su file.
*   - � stata posta molta attenzione sulla gestione degli errori.
*   - altri vincoli inseriti nelle descrizione delle funzioni.
*   - Le funzioni Riordina() e ControllaOrdinato() non vengono utilizzate nel programma sono solo per dimostrare che sono
*       in grado di programmarle...
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

/*  Costanti    */
const int VEC_LUNG = 150;
const char CARATTERE_DIVISORE = '|';

/*  Costanti per la gestione degli errori. Sarebbero state meglio come uno o pi� enum,
*   ma questo metodo non � stato spiegato in classe.
*/
const int ERR_VOCABOLO_ESISTENTE = -2;
const int ERR_VETTORE_PIENO = -1;
const int ERR_FILE_NON_APERTO = -1;
const int ERR_FORMATO_NON_VALIDO = -2;
const int ERR_VOCABOLI_NON_IN_ORDINE = -3;

/*  Struttura Vocabolo : immagazzina il vocabolo in lingua primaria e secondario    */
struct Vocabolo {
    string vocaboloLinguaPrimaria;
    string vocaboloLinguaSecondaria;
};

/*  Prototipi funzioni  */
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
void Riordina(Vocabolo[], int);
bool ControllaOrdinato(Vocabolo[], int);

int main() {
    Vocabolo vecVocaboli[VEC_LUNG];
    int lung = 0;

    string nomeLinguaPrimaria, nomeLinguaSecondaria;

    /*  Richiesta nome della lingua originale e straniera.  */
    cout << "Inserire il nome della lingua originale: ";
    nomeLinguaPrimaria = CinGetLine();
    cout << "Inserire il nome della lingua straniera: ";
    nomeLinguaSecondaria = CinGetLine();

    /*  Ciclo menu principale   */
    char risposta;
    do {
        risposta = Menu();

        /*  Analisi risposta    */
        switch (risposta) {
        case '1': {
            /*  Inserimento vocabolo e analisi valore ritornato */
            int res = InserisciVocabolo(vecVocaboli, lung, ChiediVocabolo(nomeLinguaPrimaria, nomeLinguaSecondaria));
            switch (res) {
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
            /*  Rimozione vocabolo e analisi valore ritornato   */
            if (!RimuoviVocabolo(vecVocaboli, lung, ChiediParola(nomeLinguaPrimaria))) {
                cout << "Il vocabolo specificato non e'esistente!" << endl;
            }
            else {
                cout << "Vocabolo rimosso senza problemi!" << endl;
            }

            break;
        }
        case '3': {
            Vocabolo vocabolo;

            /*  Richiesta vocabolo. Nota: anche se 'vocabolo.vocaboloLinguaPrimaria' contiene il carattere divisore, non sar� possibile trovare il vocabolo
            *   quindi non � necessario utilizzare ChiediParola(). 'vocabolo.vocaboloLinguaSecondaria' invecie non pu� contenere il carattere divisore, quindi
            *   viene utilizzata la funzione ChiediParola().
            */
            cout << "Inserire la parola in " << nomeLinguaPrimaria << " di cui si vuole modificare la traduzione: ";
            vocabolo.vocaboloLinguaPrimaria = CinGetLine();
            vocabolo.vocaboloLinguaSecondaria = ChiediParola(nomeLinguaSecondaria);

            /*  Modifica vocabolo e analisi valore ritornato    */
            if (!ModificaVocabolo(vecVocaboli, lung, vocabolo)) {
                cout << "Il vocabolo specificato non e'esistente!" << endl;
            }
            else {
                cout << "Vocabolo modificato senza problemi!" << endl;
            }

            break;
        }
        case '4': {
            /*  Visualizzazione vocabolario */
            VisualizzaVocabolario(vecVocaboli, lung);
            break;
        }
        case '5': {
            /*  Richiesta nome del file */
            string nomeFile;
            cout << "Inserire il nome del file sul quale si vuole salvare il vocabolario: ";
            nomeFile = CinGetLine();

            /*  Salvataggio vocabolario ed analisi valore ritornato */
            if (!SalvaVocabolario(vecVocaboli, lung, nomeFile)) {
                cout << "Non e' stato possibile salvare il vocabolario!" << endl;
            }
            else {
                cout << "Vocabolario salvato con successo!" << endl;
            }

            break;
        }
        case '6': {
            /*  Richiesta nome del file */
            string nomeFile;
            cout << "Inserire il nome del file dal quale si vuole caricare il vocabolario: ";
            nomeFile = CinGetLine();

            /*  Caricamento vocabolario ed analisi valore ritornato */
            int res = CaricaVocabolario(vecVocaboli, lung, nomeFile);
            switch (res) {
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
    } while (risposta != '0');

    return 0;
}

/*  Funzione Menu()
*   Questa funzione stampa il menu e prende la risposta dell'utente.
*   La risposta viene analizzata nel main().
*/
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

/*  Funzione ChiediVocabolo()
*   Questa funzione chiede all'utente un vocabolo, quindi chiede la parola nella lingua
*   principale e nella lingua secondaria.
*/
Vocabolo ChiediVocabolo(string nomeLinguaPrimaria, string nomeLinguaSecondaria) {
    Vocabolo vocabolo;

    vocabolo.vocaboloLinguaPrimaria = ChiediParola(nomeLinguaPrimaria);
    vocabolo.vocaboloLinguaSecondaria = ChiediParola(nomeLinguaSecondaria);

    cout << vocabolo.vocaboloLinguaPrimaria << " " << vocabolo.vocaboloLinguaSecondaria << endl;

    return vocabolo;
}

/*  Funzione ChiediParola()
*   Questa funzione chiede una singola parola in una lingua specificata in input.
*   Controlla anche che la parola non contenga il carattere il carattere divisore, in quanto questo
*   carattere � utilizzato come divisore quando il dizionario viene salvato o
*   caricato da file.
*/
string ChiediParola(string nomeLingua) {
    string parola;

    bool ok;
    do {
        cout << "Inserire il vocabolo in " << nomeLingua << ": ";
        /*  Utilizzo di CinGetLine() per prendere in input l'intera riga e per poter 
        *   prendere vocaboli conteneti lo spazio
        */
        parola = CinGetLine();
        //cin >> parola;

        /*  Se parola.find(CARATTERE_DIVISORE) � diverso da -1, allora la parola contiene il carattere il carattere divisore */
        ok = (parola.find(CARATTERE_DIVISORE) == -1);

        if (!ok) {
            cout << "Il vocabolo non puo' contenere il carattere '" << CARATTERE_DIVISORE << "' !" << endl;
        }
    } while (!ok);

    return parola;
}

/*  Funzione InserisciVocabolo()
*   Questa funzione inserisce un vocabolo nel vettore dei vocaboli. L'inserimento
*   viene effettuato in modo che i vocaboli siano direttamente inseriti in ordine
*   alfabetico. Viene inoltre controllato se il vettore � pieno e se il vocabolo
*   da inserire � gi� stato inserito.
* 
*   Valore di ritorno:
*   - 0                             : nessun errore
*   - ERR_VETTORE_PIENO(-1)         : vettore pieno
*   - ERR_VOCABOLO_ESISTENTE(-2)    : vocabolo gi� esistente
*/
int InserisciVocabolo(Vocabolo vecVocaboli[], int& lung, Vocabolo vocabolo) {
    /*  Controllo lunghezza vettore */
    if (lung >= VEC_LUNG - 1) {
        return ERR_VETTORE_PIENO;
    }

    /*  Ricerca posizione ottimale. Se TrovaPosizioneOttimale() ritorna true, allora
    *   vuol dire che un vocabolo identico � stato trovato, quindi usciamo dalla funzione.
    */
    int pos;
    if (TrovaPosizioneOttimale(pos, vecVocaboli, lung, vocabolo.vocaboloLinguaPrimaria)) {
        return ERR_VOCABOLO_ESISTENTE;
    }

    /*  Creazione spazio nel vettore*/
    for (int i = lung; i > pos; i--) {
        vecVocaboli[i] = vecVocaboli[i - 1];
    }
    vecVocaboli[pos] = vocabolo;
    lung++;

    /*  Se siamo arrivati fin qui, allora non abbiamo avuto problemi.   */
    return 0;
}

/*  Funzione TrovaVocabolo()
*   Questa funzione effettua la ricerca binaria sui vocaboli in lingua primaria in tutto
*   il vettore e ritorna la posizione del vocabolo desiderato. Se il vocabolo non viene
*   trovato allora viene ritornato il valore -1.
*/
int TrovaVocabolo(Vocabolo vecVocaboli[], int lung, string vocaboloLinguaPrimaria) {
    int sup = lung - 1;
    int inf = 0;
    int center;

    /*  Nota: il ciclo viene saltato se lung � 0 (vettore vuoto), quindi non ci sono problemi
    *   con i casi limite.
    */
    while (inf <= sup) {
        center = (sup + inf) / 2;

        if (vecVocaboli[center].vocaboloLinguaPrimaria == vocaboloLinguaPrimaria) {
            /*  Vocabolo trovato. Ritorno della posizione.  */
            return center;
        }
        if (vecVocaboli[center].vocaboloLinguaPrimaria > vocaboloLinguaPrimaria) {
            sup = center - 1;
        }
        else if (vecVocaboli[center].vocaboloLinguaPrimaria < vocaboloLinguaPrimaria) {
            inf = center + 1;
        }
    }

    /*  Vocabolo non trovato. Ritorno di -1.    */
    return -1;
}

/*  Funzione RimuoviVocabolo()
*   Questa funzione rimuove un vocabolo dal vettore. Se il vocabolo desiderato (indicato
*   con il vocabolo in lungua primaria) non viene trovato viene ritornato il valore false.
*   Se la rimozione � avvenuta con successo viene ritornato invece il valore true.
*/
bool RimuoviVocabolo(Vocabolo vecVocaboli[], int& lung, string vocaboloLinguaPrimaria) {
    /*  Troviamo la posizione del vocabolo. Se pos == -1, allora il vocabolo non esiste.    */
    int pos = TrovaVocabolo(vecVocaboli, lung, vocaboloLinguaPrimaria);
    if (pos == -1) {
        return false;
    }

    /*  Rimozione del vocabolo e compattamento del vettore. */
    for (int i = pos; i < lung - 1; i++) {
        vecVocaboli[i] = vecVocaboli[i + 1];
    }
    lung--;

    return true;
}

/*  Funzione ModificaVocabolo()
*   Questa funzione modifica un vocabolo nel vettore. Ritorna true se la modifica � avvenuta
*   con successo, se no false.
*/
bool ModificaVocabolo(Vocabolo vecVocaboli[], int lung, Vocabolo vocabolo) {
    /*  La variabile vocabolo � utilizzata per trovare la posizione del vocabolo(attraverso
    *   vocabolo.vocaboloLinguaPrimaria) e per settare il nuovo valore alla posizione trovata
    *   (attraverso vocabolo.vocaboloLinguaSecondaria).
    */

    /*  Troviamo la posizione del vocabolo. Se pos == -1, allora il vocabolo non esiste.    */
    int pos = TrovaVocabolo(vecVocaboli, lung, vocabolo.vocaboloLinguaPrimaria);
    if (pos == -1) {
        return false;
    }

    /*  Effettuazione modifica  */
    vecVocaboli[pos].vocaboloLinguaSecondaria = vocabolo.vocaboloLinguaSecondaria;

    return true;
}

/*  Funzione TrovaPosizioneOttimale()
*   Questa funzione trova la posizione ottimale per un nuovo vocabolo da inserire nel vettore,
*   facendo in modo che il vettore sia sempre ordinato.
*   La funzione controlla anche se il vocabolo da inserire sia duplicato. Se cos� fosse il valore
*   ritornato sarebbe true, se no false.
*   Si da per scontato che il vettore sia gi� ordinato.
*/
bool TrovaPosizioneOttimale(int& pos, Vocabolo vecVocaboli[], int lung, string vocaboloLinguaPrimaria) {
    /*  Settaggio sentinella per ricerca.   */
    vecVocaboli[lung].vocaboloLinguaPrimaria = vocaboloLinguaPrimaria;

    /*  Scansionamento vettore. */
    int i = 0;
    while (vecVocaboli[i].vocaboloLinguaPrimaria < vocaboloLinguaPrimaria) {
        i++;
    }

    /*  Se la posizione ottimale trovata � uguale alla parola da inserire, ma non siamo alla fine del vettore(non �
    *   stata trovata la sentinella) vuol dire che la parola � stata gi� precedentemente inserita. Il valore ritornato
    *   � true (valore duplicato).
    */
    if (vecVocaboli[i].vocaboloLinguaPrimaria == vocaboloLinguaPrimaria && i != lung) {
        return true;
    }

    /*  Settaggio posizione e ritorno false (valore non duplicato)  */
    pos = i;
    return false;
}

/*  Funzione VisualizzaVocabolario()
*   Questa funzione visualizza il vocabolario.
*/
void VisualizzaVocabolario(Vocabolo vecVocaboli[], int lung) {
    cout << "Numero vocaboli: " << lung << endl;

    for (int i = 0; i < lung; i++) {
        cout << vecVocaboli[i].vocaboloLinguaPrimaria << ": " << vecVocaboli[i].vocaboloLinguaSecondaria << endl;
    }
}

/*  Funzione SalvaVocabolario()
*   Questa funzione salva il vocabolario su un file specificato in input.
*   Il formato del salvataggio prevede che ogni linea contenga un vocabolo
*   (quindi 2 parole di diverse lungue), dividendo le singole parole con il carattere divisore.
*   La funzione ChiediParola() assicura che le parole presenti nel vocabolario
*   non contengano tale carattere.
*   La funzione ritorna true se � stato possibile salvare il vocabolario, se no
*   false.
*/
bool SalvaVocabolario(Vocabolo vecVocaboli[], int lung, string nomeFile) {
    /*  Apertura file   */
    fstream fileStream;
    fileStream.open(nomeFile.c_str(), ios::out);

    /*  Controllo se file valido    */
    if (!fileStream.is_open()) {
        return false;
    }

    /*  Salvataggio */
    for (int i = 0; i < lung; i++) {
        fileStream << vecVocaboli[i].vocaboloLinguaPrimaria << "|" << vecVocaboli[i].vocaboloLinguaSecondaria << endl;
    }

    fileStream.close();

    return true;
}

/*  Funzione CaricaVocabolario()
*   Questa funzione carica il vocabolario da un file.
*   Si presuppone che il fil file contenga un vocabolario ordinato e che utilizzi
*   il corretto formato (vedere descrizione funzione SalvaVocabolario()).
*   Se avviene un errore la lunghezza dell'array viene settata a 0.
*   
*   Valore di ritorno:
*   0                               : nessun errore
*   ERR_FILE_NON_APERTO(-1)         : non � stato possibile aprire il file
*   ERR_FORMATO_NON_VALIDO(-2)      : formato non riconosciuto
*   ERR_VOCABOLI_NON_IN_ORDINE(-3)  : vocaboli non in ordine (anche vocabolo duplicato)
*/
int CaricaVocabolario(Vocabolo vecVocaboli[], int& lung, string nomeFile) {
    /*  Apertura file   */
    ifstream fileStream;
    fileStream.open(nomeFile.c_str(), ios::in);

    /*  Controllo se file valido    */
    if (!fileStream.is_open()) {
        lung = 0;

        return ERR_FILE_NON_APERTO;
    }

    lung = 0;

    /*  Analisi linea per linea.    */
    string linea;
    while (getline(fileStream, linea)) {
        /*  Se non � possibile trovare il carattere divisore, allora il formato probabilmente non � corretto.    */
        int posCarateereDivisore = linea.find(CARATTERE_DIVISORE);
        if (posCarateereDivisore == -1) {
            lung = 0;

            return ERR_FORMATO_NON_VALIDO;
        }
        
        /*  salvataggio vocaboli    */
        vecVocaboli[lung].vocaboloLinguaPrimaria = linea.substr(0, posCarateereDivisore);
        vecVocaboli[lung].vocaboloLinguaSecondaria = linea.substr(posCarateereDivisore + 1, linea.size());

        /*  Controllo ordine    */
        if (lung > 0 && vecVocaboli[lung].vocaboloLinguaPrimaria <= vecVocaboli[lung - 1].vocaboloLinguaPrimaria) {
            lung = 0;

            return ERR_VOCABOLI_NON_IN_ORDINE;
        }

        lung++;
    }

    fileStream.close();

    return 0;
}

/*  Funzione CinGetLine()
*   Questa funzione prende una stringa dal cin mantenendo gli spazi.
*   Questa funzione sarebbe meglio come una macro o una funzione inline,
*   ma questi metodi non sono stati spiegati in classe.
*/
string CinGetLine() {
    string s;

    /*  cin.sync();
    *   cin.clear();
    *   cin.ignore();
    */
    getline(cin >> ws, s);

    return s;
}

/*  Funzione ControllaOrdinato()
*   Questa funzione controlla se il vettore è ordinato.
*/
bool ControllaOrdinato(Vocabolo vecVocaboli[], int lung) {
    int i = 0;
    while(i < (lung - 1) && vecVocaboli[i].vocaboloLinguaPrimaria <= vecVocaboli[i + 1].vocaboloLinguaPrimaria) {
        i++;
    }

    if (i == (lung - 1)) {
        return true;
    }

    return false;
}

/*  Funzione Riordina()
*   Questa funzione riordina il vettore in un metodo molto efficiente... ;-)
*/
void Riordina(Vocabolo vecVocaboli[], int lung) {
    srand(time(NULL));

    /*  BOGO SORT TIME!!!   */
    while(!ControllaOrdinato(vecVocaboli, lung)) {
        int pos1 = rand() % lung;
        int pos2 = rand() % lung;

        Vocabolo temp = vecVocaboli[pos1];
        vecVocaboli[pos1] = vecVocaboli[pos2];
        vecVocaboli[pos2] = temp;
    }

    /*  Sorting serio...    BUBBLE SORT TIME!!!
    *   int sup = lung - 1;
    *   int us;
    * 
    *   do {
    *       us = -1;
    * 
    *       for (int i = 0; i < lung - 1; i++) {
    *           if (vecVocaboli[i].vocaboloLinguaPrimaria > vecVocaboli[i + 1].vocaboloLinguaPrimaria) {
    *               Vocabolo temp = vecVocaboli[i];
    *               vecVocaboli[i] = vecVocaboli[i + 1];
    *               vecVocaboli[i + 1] = temp;
    * 
    *               us = i;
    *           }
    *       }
    * 
    *       sup = us;
    *   } while(us != -1);
    */
}
