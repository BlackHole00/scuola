#pragma once
#include <string>

using namespace std;

/* Classe di supposto per salvare il nome degli animali o le domande per il gioco.
*  La classe contiene una stringa data che contiene un nome o una domanda ed un flag
*  isQuestion che indica se che tipo di informazione è stata salvata.
*  Non e'strettamente necessaria, in quanto e'possibile identificare se un nodo contiene
*  un animale controllando se esso sia una foglia. Il principale motivo di mantenere
*  comunque questa classe e'per una futura facile espanzione del programma (nel caso,
*  per esempio, che si voglia utilizzare un albero non binario, che abbia piu'risposte
*  per ogni nodo o nel caso si voglia anche offrire una descrizione dell'animale
*  indovinato.)
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