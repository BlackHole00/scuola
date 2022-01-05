#include "game.h"

#include <iostream>
#include <assert.h>
#include <sstream>
#include <fstream>

#include "utils.h"

using namespace std;

Game::Game(string saveFile) {
    tree = BTree<Element>();
    this->saveFile = saveFile;
}

void Game::Clear() {
    tree = BTree<Element>();

    InsertFirstAnimal();
}

bool Game::Save() {
    /*  Se il file non è valido, ritorna false. */
    ofstream stream(saveFile.c_str());
    if (!stream.is_open()) {
        return false;
    }

    string resource = Serialize();
    stream << resource;

    return true;
}

bool Game::Load() {
    /*  Se il file non è valido, ritorna false. */
    ifstream stream(saveFile.c_str());
    if (!stream.is_open()) {
        return false;
    }

    string resource;
    getline(stream, resource);

    Deserialize(resource);

    return true;
}

/* Funzione ricorsiva.
*  Struttura per un nodo:
*   - se il nodo è NULL, allora viene identificato con '#'
*   - altrimenti:
*       - il primo carattere identifica se il nodo contiene una domanda o un animale ('1' o '0')
*       - i caratteri successivi fino al primo '|' contiengono la stringa.
*       - successivamente vengono rappresentati, ricorsivamente, il nodo di sinistra e di destra.
*   - quindi viene fatto un salvataggio INORDER.
*
*  Esempio:
*   1acqua?|0gatto|##0trota|##
*
*       DOMANDA: acqua?
*       |NO           |SI
*       V             V
*   ANIM: gatto   ANIM: trota
*   |     |      |      |
*   V     V      V      V
*   NULL  NULL   NULL   NULL
*/
string Game::Serialize(BTreeNode<Element>* node) {
    if (node == NULL) {
        return "#";
    }

    stringstream ss;
    ss << (int)node->GetData().IsQuestion() << node->GetData().GetData() << "|" << Serialize(node->GetLeftNode()) << Serialize(node->GetRightNode());

    return ss.str();
}

/*  Funzione ricorsiva.
*   Legge la parte interessata della stringa in input e crea un nodo con le corrispondenti informazioni.
*   Facendo questo aggiorna anche startPos, facendo in modo che la prossima chiamata faccia riferimento
*   alla giusta parte della stringa. Vedi Serialize() per maggiori informazioni.
*/
BTreeNode<Element>* Game::Deserialize(int& startPos, string resource) {
    /* Si ricorda che se il carattere è '#', allora stiamo analizzando un nodo vuoto (NULL). */
    if (resource[startPos] == '#') {
        startPos++;

        return NULL;
    }

    BTreeNode<Element>* newNode = new BTreeNode<Element>();

    /* Estrazione data e flag isQuestion. */
    string data = resource.substr(startPos + 1, resource.find_first_of('|', startPos) - startPos - 1);
    bool isQuestion = (resource[startPos] == '1');

    /* Update nodo. */
    newNode->GetDataPtr()->SetIsQuestion(isQuestion);
    newNode->GetDataPtr()->SetData(data);

    /* Calcolo nuovo startPos per le prossime chiamate Deserialize(). */
    startPos = resource.find_first_of('|', startPos) + 1;

    /* Chiamata ricorsiva per il nodo di destra e di sinistra. */
    newNode->SetLeftNode(Deserialize(startPos, resource));
    newNode->SetRightNode(Deserialize(startPos, resource));

    return newNode;
}

void Game::InsertFirstAnimal() {
    string question;
    string animal1;
    string animal2;

    cout << "Inserisci una nuova domanda: ";
    getline(cin >> ws, question);

    cout << "Insersci un animale che rispetta la caratteristica: ";
    getline(cin >> ws, animal2);

    cout << "Insersci un animale che non rispetta la caratteristica: ";
    getline(cin >> ws, animal1);

    /* Creazione primo nodo. */
    Element element = Element(question, true);
    BTreeNode<Element>* node = new BTreeNode<Element>(element);

    /* Creazione e settaggio nuovi nodi. */
    Element leftElement = Element(animal1, false);
    Element rightElement = Element(animal2, false);

    node->SetLeftNode(new BTreeNode<Element>(leftElement));
    node->SetRightNode(new BTreeNode<Element>(rightElement));

    /* Aggiornamento primo nodo. */
    tree.SetRoot(node);
}

bool Game::Play() {
    /* L'albero non deve essere vuoto. Se questo accade è un errore del programmatore.  */
    assert(!tree.IsEmpty());

    BTreeNode<Element>* node = tree.GetRoot();

    /*  Avanziamo nell'albero finchè non raggiungiamo un nodo che non è una domanda. */
    while (node->GetData().IsQuestion()) {
        if (AskQuestion(node->GetData().GetData()) == 'n') {
            node = node->GetLeftNode();
        } else {
            node = node->GetRightNode();
        }
    }

    /* Se l'animale non è corretto, allora viene chiesta una nuova domanda all'utente e viene ritornato true. */
    if (AskQuestion("L' animale e' " + node->GetData().GetData() + "! E' corretto? ") == 'n') {
        cout << "Oh No!!!" << endl;
        InsertAnimal(node);

        return true;
    } else {
        cout << "Perfetto!!!" << endl;

        return false;
    }
}