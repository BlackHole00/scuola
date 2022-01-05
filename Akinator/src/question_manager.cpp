#include "question_manager.h"

#include <assert.h>

#include "utils.h"

QuestionManager::QuestionManager(Game* game) {
    this->game = game;
}

void QuestionManager::Run() {
    /* L'albero non deve essere vuoto. Se lo e', c'e' stato un errore da parte del programmatore. */
    currentNode = game->GetTreeRoot();
    assert(currentNode != NULL);

    char resp;
    do {
        resp = Menu();

        switch(resp) {
            case '1': {
                string str;

                if (currentNode->GetData().IsQuestion()) {
                    cout << "Inserisci la nuova domanda: ";
                } else {
                    cout << "Inserisci il nuovo animale: ";
                }

                getline(cin >> ws, str);

                currentNode->GetDataPtr()->SetData(str);

                break;
            }
            case '2': {
                if (!currentNode->GetData().IsQuestion()) {
                    InsertAnimal(currentNode);
                } else {
                    cout << "Non sei alla fine dell'albero!" << endl;
                }

                break;
            }
            case '3': {
                if (currentNode->GetRightNode() != NULL) {
                    currentNode = currentNode->GetRightNode();
                } else {
                    cout << "Sei gia' alla fine!!!" << endl;
                }
                break;
            }
            case '4': {
                if (currentNode->GetLeftNode() != NULL) {
                    currentNode = currentNode->GetLeftNode();
                } else {
                    cout << "Sei gia' alla fine!!!" << endl;
                }
                break;
            }
            case '5': {
                currentNode = game->GetTreeRoot();
                break;
            }
            case '6': {
                game->Clear();
                break;
            }
            case '7': {
                if (!game->Save()) {
                    cout << "Non e' stato possibile salvare." << endl;
                }

                break;
            }
            case '8': {
                if (!game->Load()) {
                    cout << "Non e' stato possibile caricare." << endl;
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
    } while(resp != '0');
}

char QuestionManager::Menu() {
    cout << "-----Gestione domande-----" << endl;
    if (currentNode->GetData().IsQuestion()) {
        cout << " Domanda attuale: " << currentNode->GetData().GetData() << endl;
        cout << " Percorso positivo: " << currentNode->GetRightNode()->GetData().GetData() << endl;
        cout << " Percorso negativo: " << currentNode->GetLeftNode()->GetData().GetData() << endl << endl;
    } else {
        cout << " Animale attuale: " << currentNode->GetData().GetData() << endl << endl;
    }
    cout << "[1]: Modifica la domanda/animale attuale" << endl;
    cout << "[2]: Inserisci una domanda" << endl;
    cout << "[3]: Continua al percorso positivo" << endl;
    cout << "[4]: Continua al percorso negativo" << endl;
    cout << "[5]: Ritorna alla prima domanda" << endl;
    cout << "[6]: Resetta" << endl;
    cout << "[7]: Salva su file" << endl;
    cout << "[8]: Carica da file" << endl;
    cout << "[0]: Ritorna al gioco" << endl;
    cout << "Risposta: ";

    char resp;
    cin >> resp;

    return resp;
}