#pragma once
#include <string>

using namespace std;

/* Classe di supposto per salvare il nome degli animali o le domande per il gioco.
*  La classe contiene una stringa data che contiene un nome o una domanda ed un flag
*  isQuestion che indica se che tipo di informazione è stata salvata.
*/
class Element {
private:
    bool isQuestion;
    string data;

public:
    Element();
    Element(string data, bool isQuestion);
    Element(const Element& element);

    void SetIsQuestion(bool isQuestion);
    void SetData(string data);

    bool IsQuestion();
    string GetData();
};