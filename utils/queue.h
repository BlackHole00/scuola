#pragma once

template <class T>
struct QueueNode {
    T data;
    QueueNode* next_node;
};

template <class T>
class Queue {
private:
    QueueNode<T>* first_node;
    QueueNode<T>* last_node;
    unsigned int length;

public:
    Queue() {
        first_node = NULL;
        last_node = NULL;
        length = 0;
    }

    ~Queue() {
        Empty();
    }

    void Enqueue(T value) {
        if (last_node == NULL) {
            last_node = new QueueNode<T>();
            first_node = last_node;
            first_node->next_node = last_node;
        } else {
            last_node->next_node = new QueueNode<T>();
            last_node = last_node->next_node;
            last_node->next_node = NULL;
        }

        last_node->data = value;

        length++;
    }

    void Dequeue() {
        if (first_node != NULL) {
            QueueNode<T>* node = first_node;

            first_node = first_node->next_node;

            delete node;
            length--;
        }
    }

    void Empty() {
        while(!IsEmpty()) {
            Dequeue();
        }
    }

    T Front() const {
        return first_node->data;
    }

    T DequeueReturn() {
        T value = Front();
        Dequeue();

        return value;
    }

    bool IsEmpty() const {
        return length == 0;
    }

    unsigned int Length() const {
        return length;
    }
};