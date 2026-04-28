/*
Author: Esteban Pereira das Neves
Project: RESET - A Text Adventure Game
Course: CPSC-25-12703 (Spring 2026)
*/

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