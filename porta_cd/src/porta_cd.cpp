#include "porta_cd.h"
#include <sstream>

PortaCd::PortaCd() {
    vecCd = new Cd[0];
    maxSize = 0;
}

PortaCd::PortaCd(int size) {
    vecCd = new Cd[size];
    maxSize = size;
}

PortaCd::~PortaCd() {
    delete[] vecCd;
}

Cd& PortaCd::GetCd(int position) {
    return vecCd[position];
}

void PortaCd::SetCd(Cd cd, int position) {
    if (position >= 0 && position < maxSize) {
        vecCd[position] = cd;
    }
}

void PortaCd::KillCd(int position) {
    if (position >= 0 && position < maxSize) {
        vecCd[position] = Cd(); /*  Utilizzo costruttore di default */
    }
}

int PortaCd::GetNumeroCd() const {
    int count = 0;
    
    for (int i = 0; i < maxSize; i++) {
        if (vecCd[i].GetDurata() != -1) {   /*  Se il dato è quello di default, allora il cd non è stato inserito   */
            count++;
        }
    }

    return count;
}

int PortaCd::CercaCdPerTitolo(string titolo) const {
    int i = 0;
    while(i < maxSize && vecCd[i].GetTitolo() == titolo) {
        i++;
    }

    if (i == maxSize) {
        return -1;
    }

    return i;
}

string PortaCd::ToString() const {
    string str;
    stringstream ss(str);

    ss << "PortaCd: " << GetNumeroCd() << "cd (" << maxSize << " cd max)" << endl;
    for (int i = 0; i < maxSize; i++) {
        if (vecCd[i].GetDurata() != -1) {   /*  Se il dato è quello di default, allora il cd non è stato inserito   */
            ss << vecCd[i].ToString();
        }
    }

    return str;
}

int PortaCd::CmpPortaCd(const PortaCd& other) const {
    int count = 0;
    
    for (int i = 0; i < maxSize; i++) {
        if (other.CercaCdPerTitolo(vecCd[i].GetTitolo()) != -1) {
            count++;
        }
    }

    return count;
}

ostream& operator<<(ostream& os, const PortaCd& portaCd) {
    os << portaCd.ToString();
    
    return os;
}
