#pragma once
#include "biglietto.h"
#include <queue.h>

class Gioco {
private:
    Queue<Biglietto> biglietti;
    string linguaPrincipale;
    string linguaStraniera;
    int numErrori;

public:
    Gioco();
    
    void InizializzaGioco();
    bool InizializzaGiocoDaFile(string);

    int Run();

    bool SalvaSuFile(string);
};