#ifndef RESETMANAGER_H
#define RESETMANAGER_H

#include <string>
#include "PlayerState.h"

using namespace std;

/*
Handles deaths and resets. The player loses temporary progress,
but keeps memories learned from previous attempts
*/

class ResetManager {
public:
    void triggerReset(PlayerState& player);
    void displayResetMessage(const PlayerState& player, string memoryGained) const;
};

#endif