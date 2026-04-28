#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include "Choice.h"

using namespace std;

/*
This class is for the scenes of the game
A scene has an ID, a description, and a list of choices.

*/

class Scene {
private:
    int id;
    string description;
    vector<Choice> choices;

public:
    Scene();
    Scene(int sceneId, string sceneDescription);

    int getId() const;
    string getDescription() const;

    void addChoice(Choice choice);
    vector<Choice> getChoices() const;

    void displayScene() const;
};

#endif