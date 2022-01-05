#pragma once
#include "b_tree.h"

#include <iostream>

template <class T>
BTree<T>::BTree() {
    root = NULL;
}

template <class T>
BTree<T>::BTree(BTreeNode<T>* root) {
    this->root = root;
}

template <class T>
BTreeNode<T>* BTree<T>::ABRInsert(BTreeNode<T>* node, T data) {
    if (node == NULL) {
        return new BTreeNode<T>(data);
    }

    if (data > node->getData()) {
        node->SetRightNode(ABRInsert(node, data));
    } else {
        node->SetLeftNode(ABRInsert(node, data));
    }

    return node;
}

template <class T>
void BTree<T>::PreOrderPrint(BTreeNode<T>* node) const {
    if (node == NULL) {
        return;
    }

    std::cout << node->GetData() << std::endl;
    PreOrderPrint(node->GetLeftNode());
    PreOrderPrint(node->GetRightNode());
}

template <class T>
void BTree<T>::PostOrderPrint(BTreeNode<T>* node) const {
    if (node == NULL) {
        return;
    }

    PostOrderPrint(node->GetLeftNode());
    PostOrderPrint(node->GetRightNode());
    std::cout << node->GetData() << std::endl;
}

template <class T>
void BTree<T>::InOrderPrint(BTreeNode<T>* node) const {
    if (node == NULL) {
        return;
    }

    InOrderPrint(node->GetLeftNode());
    std::cout << node->GetData() << std::endl;
    InOrderPrint(node->GetRightNode());
}

template <class T>
int BTree<T>::NumberOfNodes(BTreeNode<T>* node) const {
    if (node == NULL) {
        return 0;
    }

    int n = 1;
    n += NumberOfNodes(node->GetLeftNode());
    n += NumberOfNodes(node->GetRightNode());

    return n;
}

template <class T>
int BTree<T>::NumberOfLeaves(BTreeNode<T>* node) const {
    if (node == NULL) {
        return 0;
    }

    if (node->GetLeftNode() == NULL && node->GetRightNode() == NULL) {
        return 1;
    }

    int n = 0;
    n += NumberOfLeaves(node->GetLeftNode());
    n += NumberOfLeaves(node->GetRightNode());

    return n;
}

template <class T>
void BTree<T>::Remove(BTreeNode<T>* superiorNode, BTreeNode<T>* node) {
    if (node == NULL) {
        return;
    }

    Remove(node, node->GetLeftNode());
    Remove(node, node->GetRightNode());

    delete node;
    if (superiorNode->GetLeftNode() == node) {
        superiorNode->SetLeftNode(NULL);
    } else {
        superiorNode->SetRightNode(NULL);
    }
}