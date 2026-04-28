#include <iostream>
#include "ResetManager.h"

using namespace std;

void ResetManager::triggerReset(PlayerState& player) {
    player.addDeath();
    player.resetForNewRun();
}

void ResetManager::displayResetMessage(const PlayerState& player, string memoryGained) const {
    cout << endl;
    cout << "Everything goes black..." << endl;
    cout << "You wake up again in the same room." << endl;
    cout << "RESET #" << player.getDeaths() << endl;
    cout << endl;

    if (memoryGained != "") {
        cout << "New memory gained: " << memoryGained << endl;
    }

    cout << "You lost everything you were carrying." << endl;
    cout << "But you still remember what happened." << endl;
    cout << endl;
}