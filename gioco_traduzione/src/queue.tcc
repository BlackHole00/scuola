#include "queue.h"

template <class T>
Queue<T>::Queue() {
    first_node = NULL;
    last_node = NULL;
    length = 0;
}

template <class T>
Queue<T>::~Queue() {
    Empty();
}

template <class T>
void Queue<T>::Enqueue(T value) {
    if (last_node == NULL) {
        last_node = new QueueNode<T>();
        first_node = last_node;
        last_node->next_node = NULL;
    } else {
        last_node->next_node = new QueueNode<T>();
        last_node = last_node->next_node;
        last_node->next_node = NULL;
    }

    last_node->data = value;

    length++;
}

template <class T>
void Queue<T>::Dequeue() {
    if (first_node != NULL) {
        QueueNode<T>* node = first_node;

        if (first_node == last_node) {
            last_node = NULL;
        }
        first_node = first_node->next_node;


        delete node;
        length--;
    }
}

template <class T>
void Queue<T>::Empty() {
    while(!IsEmpty()) {
        Dequeue();
    }
}

template <class T>
T Queue<T>::Front() const {
    return first_node->data;
}

template <class T>
T Queue<T>::DequeueReturn() {
    T value = Front();
    Dequeue();

    return value;
}

template <class T>
bool Queue<T>::IsEmpty() const {
    return length == 0;
}

template <class T>
unsigned int Queue<T>::Length() const {
    return length;
}