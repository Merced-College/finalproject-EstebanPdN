#ifndef RESETMANAGER_H
#define RESETMANAGER_H

#include "PlayerState.h"

/*
Handles the reset system for the game
When the player dies or reaches a bad ending, this updates
the player's death count and prepares the next run.
*/

class ResetManager {
public:
    void triggerReset(PlayerState& player);
    void displayResetMessage(const PlayerState& player) const;
};

#endif