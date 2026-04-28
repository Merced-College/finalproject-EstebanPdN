/*
Author: Esteban Pereira das Neves
Project: RESET - A Text Adventure Game
Course: CPSC-25-12703 (Spring 2026)
*/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <map>
#include <stack>
#include <string>
#include "Scene.h"
#include "PlayerState.h"
#include "ResetManager.h"

using namespace std;

/*
This manages the main game loop, scene navigation, player input,
death events, reset logic, and other conditions.
*/

class GameEngine {
private:
    map<int, Scene> buildScenes();
    string getSceneName(int sceneId) const;

    void showPlayerMemory(const PlayerState& player) const;
    void handleDeath(PlayerState& player, ResetManager& resetManager, string deathMessage, string memoryGained);

public:
    void start();
};

#endif