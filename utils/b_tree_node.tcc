#include "b_tree_node.h"
#include <cstddef>

template <class T>
BTreeNode<T>::BTreeNode() {
    leftNode = NULL;
    rightNode = NULL;
}

template <class T>
BTreeNode<T>::BTreeNode(T data) {
    this->data = data;
    leftNode = NULL;
    rightNode = NULL;
}

template <class T>
T BTreeNode<T>::GetData() const {
    return data;
}

template <class T>
T* BTreeNode<T>::GetDataPtr() {
    return &data;
}

template <class T>
BTreeNode<T>* BTreeNode<T>::GetLeftNode() const {
    return leftNode;
}

template <class T>
BTreeNode<T>* BTreeNode<T>::GetRightNode() const {
    return rightNode;
}

template <class T>
void BTreeNode<T>::SetData(T data) {
    this->data = data;
}

template <class T>
void BTreeNode<T>::SetLeftNode(BTreeNode<T>* node) {
    leftNode = node;
}

template <class T>
void BTreeNode<T>::SetRightNode(BTreeNode<T>* node) {
    rightNode = node;
}

