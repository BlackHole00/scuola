#pragma once

#include "b_tree_node.h"
#include "game.h"

/* Classe di aiuto per permettere al giocatore di gestire le domande. */
class QuestionManager {
private:
    /* Il gioco */
    Game* game;
    /* Variabile temporanea utilizzata negli algritmi */
    BTreeNode<Element>* currentNode;

    /* Visualizzazione menu' */
    char Menu();

public:
    QuestionManager(Game* game);

    void Run();
};