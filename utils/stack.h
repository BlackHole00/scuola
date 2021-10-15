#pragma once
#include <iostream>

template <class T>
class Stack {
private:
    unsigned int index;
    unsigned int memLen;
    T* stack;

public:
    Stack() {
        index = 0;
        memLen = 1;

        stack = new T[1];
    }

    ~Stack() {
        delete[] stack;
    }

    void Push(T value) {
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

    T Top() {
        return stack[index - 1];
    }

    void Pop() {
        if (index <= memLen / 2) {
            stack = (T*)realloc(stack, memLen / 2 * sizeof(T));
            if (stack == NULL) {
                exit(-1);
            }

            memLen /= 2;
        }
        index -= (index > 0 ? 1 : 0);
    }

    T PopReturn() {
        T value = Top();

        Pop();

        return value;
    }

    unsigned int Size() {
        return index;
    }

    bool IsEmpty() {
        return index <= 0;
    }
};