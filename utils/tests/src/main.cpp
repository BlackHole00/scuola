#include <iostream>
#include <s_linked_list.h>

using namespace std;

int main() {
    //  NODE TEST
    Node<int> node(30);
    cout << node.GetData() << " " << node.GetNextNode() << endl;

    //  LIST TEST
    LinkedList<int> list;
    list.InsertFirst(500);
    list.InsertFirst(400);
    list.InsertFirst(300);
    list.InsertFirst(200);
    list.InsertFirst(100);
    list.InsertLast(700);
    list.InsertLast(800);
    list.InsertLast(900);
    list.InsertLast(1000);
    list.Insert(600, 5);

    cout << list.Get(9) << endl;

    cout << list.Length() << " ";
    cout << list.ToString() << endl;

    int& refInt = list.Get(4);
    refInt = 501;
    list[5] = 601;

    cout << list.ToString() << endl;

    list.RemoveLast();
    list.RemoveFirst();

    cout << list.Length() << " ";
    cout << list << endl;

    list.Empty();
    cout << list.Length() << " ";
    cout << list.ToString() << endl;

    list.InsertFirst(100);
    list.RemoveLast();
    cout << list.Length() << " ";
    cout << list.ToString() << endl;

    return 0;
}