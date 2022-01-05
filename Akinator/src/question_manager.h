#pragma once

#include "b_tree_node.h"
#include "game.h"

class QuestionManager {
private:
    Game* game;
    BTreeNode<Element>* currentNode;

    char Menu();

public:
    QuestionManager(Game* game);

    void Run();
};