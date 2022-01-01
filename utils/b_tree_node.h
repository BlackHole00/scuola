#pragma once

template <class T>
class BTreeNode {
private:
    T data;
    BTreeNode<T>* leftNode;
    BTreeNode<T>* rightNode;

public:
    BTreeNode();
    BTreeNode(T);

    T GetData() const;
    T* GetDataPtr();
    BTreeNode<T>* GetLeftNode() const;
    BTreeNode<T>* GetRightNode() const;

    void SetData(T data);
    void SetLeftNode(BTreeNode<T>* node);
    void SetRightNode(BTreeNode<T>* node);
};

#include "b_tree_node.tcc"
