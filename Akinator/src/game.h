#pragma once
#include <b_tree.h>
#include <string>

#include "element.h"

using namespace std;

/* Questa classe gestisce il gioco, contenendo l'albero binario e fornendo funzioni d'aiuto per salvare e caricare l'albero da file */
class Game {
private:
    /* L'albero binario. I nodi di sinistra identificano le risposte negative, mentre i nodi di destra identificano le risposte positive. */
    BTree<Element> tree;
    /* Indica il node del file di salvataggio. */
    string saveFile;

    /* Data una stringa la decodifica e la applica all'albero. startPos viene utilizzato per identificare la posizione di inizio relativa al nodo corrente. */
    BTreeNode<Element>* Deserialize(int& startPos, string resource);
    /* Dato un nodo, crea una stringa che può essere decodificata con Deserialize(). */
    string Serialize(BTreeNode<Element>* node);
    /* Inserisce un nuovo animale con una nuova domanda come figlia del nodo node. */
    void InsertAnimal(BTreeNode<Element>* node);

public:
    Game(string saveFile = "save.txt");

    /* Fa partire il gioco. Ritorna true se è stata aggiunta una domanda, altrimenti false. */
    bool Play();

    /* Salva su file l'albero binario. */
    bool Save();

    /* Carica da file l'albero binario. */
    bool Load();

    /* Inserisce la prima domanda ed i primi animali. Sostituisce l'albero già esistente. */
    void InsertFirstAnimal();

    BTreeNode<Element>* GetTreeRoot() {
        return tree.GetRoot();
    }

    string Serialize() {
        return Serialize(tree.GetRoot());
    }

    void Deserialize(string resource) {
        int tmp = 0;
        tree = BTree<Element>(Deserialize(tmp, resource));
    }

    /* Azzera l'albero binario. */
    void Clear();
};