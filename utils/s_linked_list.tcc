#include "s_linked_list.h"
#include <sstream>

template <class T>
Node<T>::Node() {
    nextNode = NULL;
}

template <class T>
Node<T>::Node(T value) {
    data = value;
    nextNode = NULL;
}

template <class T>
void Node<T>::SetData(T value) {
    data = value;
}

template <class T>
void Node<T>::SetNextNode(Node<T>* node) {
    nextNode = node;
}

template <class T>
T Node<T>::GetData() const {
    return data;
}

template <class T>
T& Node<T>::GetData() {
    return data;
}

template <class T>
Node<T>* Node<T>::GetNextNode() const {
    return nextNode;
}

template <class T>
LinkedList<T>::LinkedList() {
    firstNode = NULL;
}

template <class T>
LinkedList<T>::~LinkedList() {
    Empty();
}

template <class T>
bool LinkedList<T>::IsEmpty() const {
    return firstNode == NULL;
}

template <class T>
int LinkedList<T>::Length() const {
    int i = 0;

    Node<T>* tempNode = firstNode;
    while (tempNode != NULL) {
        i++;
        tempNode = tempNode->GetNextNode();
    }

    return i;
}

template <class T>
bool LinkedList<T>::IsIndexValid(int index) const {
    return (index < Length() && index >= 0);
}


template <class T>
void LinkedList<T>::Insert(T value, int index) {
    if (!IsIndexValid(index) && index != Length()) {
        return;
    }

    Node<T>* node = new Node<T>(value);

    Node<T>* currentNode = firstNode;
    int i = 0;
    while (i < (index - 1)) {
        currentNode = currentNode->GetNextNode();

        i++;
    }

    node->SetNextNode(currentNode->GetNextNode());
    currentNode->SetNextNode(node);
}

template <class T>
void LinkedList<T>::InsertFirst(T data) {
    Node<T>* tempNode = new Node<T>(data);
    tempNode->SetNextNode(firstNode);

    firstNode = tempNode;
}

template <class T>
void LinkedList<T>::InsertLast(T data) {
    Node<T>* tempNode = new Node<T>(data);
    //  Next node is already NULL.

    Node<T>* currentNode = firstNode;
    //  If the first node is NULL, then the list is empty.
    if (currentNode == NULL) {
        firstNode = tempNode;

        return;
    }

    //  Find the last node that is NOT NULL and set the next node.
    while (currentNode->GetNextNode() != NULL) {
        currentNode = currentNode->GetNextNode();
    }
    currentNode->SetNextNode(tempNode);
}

template <class T>
T LinkedList<T>::Get(int index) const {
    T data;

    if (IsIndexValid(index)) {
        Node<T>* currentNode = firstNode;
        int i = 0;
        while (i < index) {
            currentNode = currentNode->GetNextNode();

            i++;
        }

        data = currentNode->GetData();
    }

    //  Returning garbage if the index is wrong. I don't mind.
    return data;
}

template <class T>
T& LinkedList<T>::Get(int index) {
    Node<T>* currentNode = firstNode;
    int i = 0;
    while (i < index) {
        currentNode = currentNode->GetNextNode();
        i++;
    }
    T& data = currentNode->GetData();

    //  Crash if index is wrong.
    return data;
}

template <class T>
T LinkedList<T>::RemoveFirst() {
    T data;

    if (!IsEmpty()) {
        Node<T>* tempNode = firstNode;
        data = tempNode->GetData();

        firstNode = firstNode->GetNextNode();

        delete tempNode;

    }

    //  Returning garbage if the list in empty. I don't mind.
    return data;
}

template <class T>
T LinkedList<T>::RemoveLast() {
    T data;

    if (!IsEmpty()) {
        Node<T>* currentNode = firstNode;

        //  if we don't have 2 nodes we do removeFirst.
        if (currentNode->GetNextNode() == NULL) {
            return RemoveFirst();
        }

        //  Find the node that is before the last node than is NOT NULL.
        while (currentNode->GetNextNode()->GetNextNode() != NULL) {
            currentNode = currentNode->GetNextNode();
        }

        Node<T>* tempNode = currentNode->GetNextNode();
        data = tempNode->GetData();

        currentNode->SetNextNode(NULL);
        delete tempNode;
    }

    //  Returning garbage if the list in empty. I don't mind.
    return data;
}

template <class T>
void LinkedList<T>::Empty() {
    while (!IsEmpty()) {
        RemoveFirst();
    }
}

template <class T>
string LinkedList<T>::ToString() const {
    stringstream ss;

    ss << "[ ";

    Node<T>* currentNode = firstNode;
    while (currentNode != NULL) {
        Node<T>* next = currentNode->GetNextNode();

        ss << currentNode->GetData();
        if (next != NULL) {
            ss << ", ";
        }

        currentNode = next;
    }
    ss << " ]";

    return ss.str();
}

template <class T>
T LinkedList<T>::operator[](int index) const {
    return Get(index);
}

template <class T>
T& LinkedList<T>::operator[](int index) {
    return Get(index);
}

template <class T>
ostream& operator<<(ostream& os, const LinkedList<T>& list) {
    os << list.ToString();

    return os;
}