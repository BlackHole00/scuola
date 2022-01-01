#include "element.h"

Element::Element() {
    data = "";
    isQuestion = false;
}

Element::Element(string data, bool isQuestion) {
    this->data = data;
    this->isQuestion = isQuestion;
}

Element::Element(const Element& element) {
    data = element.data;
    isQuestion = element.isQuestion;
}


void Element::SetIsQuestion(bool isQuestion) {
    this->isQuestion = isQuestion;
}

void Element::SetData(string data) {
    this->data = data;
}

bool Element::IsQuestion() {
    return isQuestion;
}

string Element::GetData() {
    return data;
}