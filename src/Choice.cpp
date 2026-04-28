#include "Choice.h"

Choice::Choice() {
    text = "";
    nextSceneId = -1;
}

Choice::Choice(string choiceText, int nextId) {
    text = choiceText;
    nextSceneId = nextId;
}

string Choice::getText() const {
    return text;
}

int Choice::getNextSceneId() const {
    return nextSceneId;
}