#include <iostream>
#include "ResetManager.h"

using namespace std;

void ResetManager::triggerReset(PlayerState& player) {
    player.addDeath();
    player.resetForNewRun();
}

void ResetManager::displayResetMessage(const PlayerState& player, string memoryGained) const {
    cout << endl;
    cout << "========================================" << endl;
    cout << "              RESET #" << player.getDeaths() << endl;
    cout << "========================================" << endl;
    cout << "Everything goes black." << endl;
    cout << "Your body is gone, but your memory remains." << endl;
    cout << "You wake up again in the first room." << endl;
    cout << endl;

    if (memoryGained != "") {
        cout << "New memory saved: " << memoryGained << endl;
    }

    cout << "Temporary progress was lost." << endl;
    cout << "Important memories were kept." << endl;
    cout << "========================================" << endl;
    cout << endl;
}