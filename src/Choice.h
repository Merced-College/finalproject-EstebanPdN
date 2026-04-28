#ifndef CHOICE_H
#define CHOICE_H

#include <string>

using namespace std;

/*
This class is for the choices that the player can make in a scene
Each choice the text displayed and an ID
*/

class Choice {
private:
    string text;
    int nextSceneId;

public:
    Choice();
    Choice(string choiceText, int nextId);

    string getText() const;
    int getNextSceneId() const;
};

#endif