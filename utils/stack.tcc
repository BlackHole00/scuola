#include "stack.h"

template <class T>
Stack<T>::Stack() {
        index = 0;
        memLen = 1;

        stack = new T[1];
    }

    
template <class T>
Stack<T>::~Stack() {
    delete[] stack;
}

template <class T>
void Stack<T>::Push(T value) {
    if (index >= memLen) {
        stack = (T*)realloc(stack, memLen * 2 * sizeof(T));
        if (stack == NULL) {
            exit(-1);
        }

        memLen *= 2;
    }

    stack[index] = value;
    index++;
}

template <class T>
T Stack<T>::Top() {
    return stack[index - 1];
}

template <class T>
void Stack<T>::Pop() {
    if (index <= memLen / 2) {
        stack = (T*)realloc(stack, memLen / 2 * sizeof(T));
        if (stack == NULL) {
            exit(-1);
        }

        memLen /= 2;
    }
    index -= (index > 0 ? 1 : 0);
}
   
template <class T>
T Stack<T>::PopReturn() {
    T value = Top();

    Pop();

    return value;
}

template <class T>
unsigned int Stack<T>::Size() {
    return index;
}

template <class T>
bool Stack<T>::IsEmpty() {
    return index <= 0;
}