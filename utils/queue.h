#pragma once

//  Struct QueueNode. Utilizzato come nodo della Queue.
//  Nota: Dovrebbe essere una classe.
template <class T>
struct QueueNode {
    T data;
    QueueNode* next_node;
};

//  Classe Queue. Utilizza una linked list per renderla dinamica
//  (senza una dimensione definita)
template <class T>
class Queue {
private:
    QueueNode<T>* first_node;
    QueueNode<T>* last_node;
    unsigned int length;

public:
    Queue();
    ~Queue();

    void Enqueue(T value);
    void Dequeue();
    void Empty();
    T Front() const;
    T DequeueReturn();

    bool IsEmpty() const;
    unsigned int Length() const;
};

//  La classe Queue e' generica. Tutte le funzioni sono dentro al file .tcc
//  Questa tecnica non nasconde il codice all'utente, ma rende non necessario
//  l'utilizzo di 'template class Queue<int>'. Questa tecnica viene anche
//  utilizzata nella libreria standard del compilatore gcc. In tale libreria non e'
//  presente nessun caso di classe con template diviso in file cpp e h, senza l'
//  utilizzo di questo trucco.
#include "queue.tcc"