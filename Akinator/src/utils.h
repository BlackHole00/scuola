#pragma once

#include <string>
#include <b_tree_node.h>

#include "element.h"

using namespace std;

/* Funzione d'aiuto per chiedere una domanda ed ottenere in ritorno 's', 'y' o 'n'. */
char AskQuestion(string string);

/* Inserisce un nuovo animale con una nuova domanda come figlia del nodo node. */
void InsertAnimal(BTreeNode<Element>* node);