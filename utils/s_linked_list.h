#pragma once
#include <string>

using namespace std;

template <class T>
class Node {
    private:
        T data;
        Node<T>* nextNode;

    public:
        Node();
        Node(T);

        void SetData(T);
        void SetNextNode(Node<T>*);
        T GetData() const;
        T& GetData();
        Node<T>* GetNextNode() const;
};

template <class T>
class LinkedList {
    template <class U> friend ostream& operator<<(ostream&, const LinkedList<U>&);

    private:
        Node<T>* firstNode;

    public:
        LinkedList();
        ~LinkedList();

        bool IsEmpty() const;
        int Length() const;
        bool IsIndexValid(int) const;

        void InsertFirst(T);
        void InsertLast(T);
        void Insert(T, int);

        T Get(int) const;
        T& Get(int);

        T RemoveFirst();
        T RemoveLast();

        void Empty();

        //  It's PUBLIC. I don't mind.
        string ToString() const;

        T operator[](int) const;
        T& operator[](int);
};


#include "s_linked_list.tcc"