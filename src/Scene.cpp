/*
Author: Esteban Pereira das Neves
Project: RESET - A Text Adventure Game
Course: CPSC-25-12703 (Spring 2026)
*/

#include <iostream>
#include "Scene.h"

using namespace std;

Scene::Scene() {
    id = -1;
    description = "";
}

Scene::Scene(int sceneId, string sceneDescription) {
    id = sceneId;
    description = sceneDescription;
}

int Scene::getId() const {
    return id;
}

string Scene::getDescription() const {
    return description;
}

void Scene::addChoice(Choice choice) {
    choices.push_back(choice);
}

vector<Choice> Scene::getChoices() const {
    return choices;
}

void Scene::displayScene() const {
    cout << description << endl;
    cout << endl;

    for (int i = 0; i < choices.size(); i++) {
        cout << i + 1 << ". " << choices[i].getText() << endl;
    }

    cout << endl;
}