#pragma once
#include <string>

using namespace std;

//  Classe Score: Tiene il punteggio ed il nome della persona che lo ha inserito.
class Score {
    //  Non c'è bisogno di altri operatori.
    friend bool operator<(const Score&, const Score&);
    friend bool operator<(const Score&, int);

    private:
        bool valid;
        string name;
        int score;

    public:
        Score();
        Score(string, int);

        int GetScore();
        string GetName();

        void SetScore(int);
        void SetName(string);

        bool IsValid();
};