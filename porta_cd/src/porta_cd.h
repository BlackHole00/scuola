#pragma once
#include <iostream>
#include "cd.h"

using namespace std;

class PortaCd {
    friend ostream& operator<<(ostream&, const PortaCd&);

private:
    Cd* vecCd;
    int maxSize;

public:
    PortaCd();
    PortaCd(int);
    ~PortaCd();

    Cd& GetCd(int);
    void SetCd(Cd, int);
    void KillCd(int);

    int GetNumeroCd() const;
    int GetMaxSize() const;

    int CercaCdPerTitolo(string) const;

    string ToString() const;

    int CmpPortaCd(const PortaCd&) const;

    bool CheckPos(int) const;
};
