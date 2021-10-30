#include "score.h"

Score::Score() {
    name = "NULL";
    score = 999;
    valid = false;
}

Score::Score(string n, int s) {
    name = n;
    score = s;
    valid = true;
}

string Score::GetName() {
    return name;
}

int Score::GetScore() {
    return score;
}

void Score::SetName(string n) {
    name = n;
    valid = true;
}

void Score::SetScore(int s) {
    score = s;
    valid = true;
}

bool Score::IsValid() {
    return valid;
}

bool operator<(const Score& s1, const Score& s2) {
    if (!s1.valid) {
        return true;
    }

    return s1.score < s2.score;
}

bool operator<(const Score& s1, int score) {
    if (s1.valid) {
        return s1.score < score;
    }

    return true;
}