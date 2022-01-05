#pragma once
#include "b_tree_node.h"

template <class T>
class BTree {
private:
    BTreeNode<T>* root;

    BTreeNode<T>* ABRInsert(BTreeNode<T>* node, T data);
    void PreOrderPrint(BTreeNode<T>* node) const;
    void PostOrderPrint(BTreeNode<T>* node) const;
    void InOrderPrint(BTreeNode<T>* node) const;
    int NumberOfNodes(BTreeNode<T>* node) const;
    int NumberOfLeaves(BTreeNode<T>* node) const;

public:
    BTree();
    BTree(BTreeNode<T>* root);
    BTree(const BTree<T>& tree);

    void ABRInsert(T data) {
        root = ABRInsert(root, data);
    }

    void PreOrderPrint() const {
        PreOrderPrint(root);
    }

    void PostOrderPrint() const {
        PostOrderPrint(root);
    }

    void InOrderPrint() const {
        InOrderPrint(root);
    }

    int NumberOfNodes() const {
        return NumberOfNodes(root);
    }

    int NumberOfLeaves() const {
        return NumberOfLeaves(root);
    }

    BTreeNode<T>* GetRoot() {
        return root;
    }

    void SetRoot(BTreeNode<T>* node) {
        root = node;
    }

    bool IsEmpty() const {
        return root == NULL;
    }

    void Remove(BTreeNode<T>* superiorNode, BTreeNode<T>* node);
};

#include "b_tree.tcc"
