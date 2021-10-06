#include "alloggio.h"

ostream& operator << (ostream& ostream, const Alloggio& alloggio) {
    cout << "Alloggio con codice: " << alloggio.codice << ", estensione: " <<
        alloggio.estensione << " mq, costo al metro quadro: " << alloggio.costoMetroQuadro <<
        " euro, percentuale tasse: " << alloggio.percentualeTasse << 
        "% e estensione calpestabile: " << alloggio.estensioneCalpestabile 
    << endl;
    
    
    return ostream;
}

Alloggio::Alloggio() {
    codice = -1;
    estensione = -1.0f;
    costoMetroQuadro = 0.0f;
    percentualeTasse = 0.0f;
    estensioneCalpestabile = -1.0f;
}

Alloggio::Alloggio(int codice,
                   float estensione,
                   float costoMetroQuadro,
                   float percentualeTasse,
                   float estensioneCalpestabile
) {
    this->codice = codice;
    this->estensione = estensione;
    this->costoMetroQuadro = costoMetroQuadro;
    this->percentualeTasse = percentualeTasse;

    if (estensioneCalpestabile <= estensione) {
        this->estensioneCalpestabile = estensioneCalpestabile;
    } else {
        this->estensioneCalpestabile = estensione;
    }
}

float Alloggio::GetEstensioneCalpestabile() {
    return estensioneCalpestabile;
}

float Alloggio::GetPercentualeTasse() {
    return percentualeTasse;
}

float Alloggio::CalcolaCostoTotaleSenzaTasse() {
    return estensione * costoMetroQuadro;
}

float Alloggio::CalcolaCostoTotaleConTasse() {
    float costo = CalcolaCostoTotaleSenzaTasse();

    return costo + (costo / 100 * percentualeTasse);
}