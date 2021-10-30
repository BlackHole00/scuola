#pragma once
#include "biglietto.h"
#include "queue.h"

//  Classe gioco.
//  Utilizzo:
//      -creare un oggetto istanza della classe
//      -utilizzare InizializzaGioco() o InizializzaGiocoDaFile()
//      -utilizzare Run()
//  Note:
//      -la queue viene modificata durante il gioco. SalvaSuFile() dovrebbe
//       essere utilizzata prima di Run()
class Gioco {
private:
    Queue<Biglietto> biglietti;
    string linguaPrincipale;
    string linguaStraniera;
    int numErrori;

public:
    Gioco();

    void AggiungiBiglietto();
    void ClearBiglietti();
    int NumBiglietti();

    void InizializzaGioco();
    bool InizializzaGiocoDaFile(string);

    int Run();

    bool SalvaSuFile(string);
};