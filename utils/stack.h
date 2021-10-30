#pragma once
#include <iostream>

//  Classe stack dinamica (allocazione della memoria dinamica utilizzata).
//  La dimensione dello stack in memoria viene raddoppiata quando si arriva
//  Alla dimensione massima.
template <class T>
class Stack {
private:
    unsigned int index;
    unsigned int memLen;
    T* stack;

public:
    Stack();
    ~Stack();

    void Push(T value);
    T Top();
    void Pop();
    T PopReturn();

    unsigned int Size();
    bool IsEmpty();
};

//  La classe e' generica. Tutte le funzioni sono dentro al file .tcc
//  Questa tecnica non nasconde il codice all'utente, ma rende non necessario
//  l'utilizzo di 'template class Stack<int>'. Questa tecnica viene anche
//  utilizzata nella libreria standard del compilatore gcc. Non e' presente
//  nessun caso di classe con template diviso in file cpp e h, senza l'utilizzo
//  di questo trucco.
#include "stack.tcc"