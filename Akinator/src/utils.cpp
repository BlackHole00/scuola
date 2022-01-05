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

void InsertAnimal(BTreeNode<Element>* node) {
    string question;
    string animal1;
    string animal2;

    cout << "Inserisci una nuova domanda: ";
    getline(cin >> ws, question);

    if (AskQuestion("L'animale " + node->GetData().GetData() + " rispetta questa caratteristica? ") == 'n') {
        animal1 = node->GetData().GetData();

        cout << "Insersci un animale che rispetta la caratteristica: ";
        getline(cin >> ws, animal2);
    } else {
        animal2 = node->GetData().GetData();

        cout << "Insersci un animale che non rispetta la caratteristica: ";
        getline(cin >> ws, animal1);
    }

    /* Aggiornamento nodo corrente. */
    node->GetDataPtr()->SetIsQuestion(true);
    node->GetDataPtr()->SetData(question);

    /* Creazione e settaggio nuovi nodi. */
    Element leftElement = Element(animal1, false);
    Element rightElement = Element(animal2, false);

    node->SetLeftNode(new BTreeNode<Element>(leftElement));
    node->SetRightNode(new BTreeNode<Element>(rightElement));
}