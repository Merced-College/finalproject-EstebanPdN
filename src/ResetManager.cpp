#include <iostream>
#include "ResetManager.h"

using namespace std;

void ResetManager::triggerReset(PlayerState& player) {
    player.addDeath();
    player.resetForNewRun();
}

void ResetManager::displayResetMessage(const PlayerState& player) const {
    cout << endl;
    cout << "Everything goes black..." << endl;
    cout << "You feel yourself waking up again." << endl;
    cout << "RESET #" << player.getDeaths() << endl;
    cout << endl;

    if (player.getDeaths() == 1) {
        cout << "This has happened before... somehow, you remember it." << endl;
    } else {
        cout << "The loop continues, but your memory is becoming clearer." << endl;
    }

    cout << endl;
}