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
Controls the main game loop, scene navigation, player input,
death events, reset logic, and all the conditions.
*/

class GameEngine {
private:
    map<int, Scene> buildScenes();
    void showPlayerMemory(const PlayerState& player) const;
    void handleDeath(PlayerState& player, ResetManager& resetManager, string deathMessage, string memoryGained);

public:
    void start();
};

#endif