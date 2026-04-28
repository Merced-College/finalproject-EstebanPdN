#include <iostream>
#include "GameEngine.h"
#include "Scene.h"
#include "Choice.h"
#include "PlayerState.h"
#include "ResetManager.h"

using namespace std;

void GameEngine::start() {
    cout << "==============================" << endl;
    cout << "RESET - A Text Adventure Game" << endl;
    cout << "==============================" << endl;
    cout << endl;

    PlayerState player;
    ResetManager resetManager;

    Scene entrance(
        1,
        "You wake up in a dark room.\n"
        "You do not remember how you got here.\n"
        "In front of you, there is a locked door.\n"
        "To your left, there is a dark hallway."
    );

    entrance.addChoice(Choice("Try to open the locked door.", 2));
    entrance.addChoice(Choice("Walk into the dark hallway.", 3));
    entrance.addChoice(Choice("Look around the room.", 4));

    entrance.displayScene();

    int playerChoice;

    cout << "Enter your choice: ";
    cin >> playerChoice;

    cout << endl;

    if (playerChoice == 1) {
        cout << "You pull on the locked door, but it does not move." << endl;
        cout << "A cold voice whispers: Not yet." << endl;
    } else if (playerChoice == 2) {
        cout << "You walk into the dark hallway." << endl;
        cout << "The floor suddenly disappears beneath you." << endl;

        resetManager.triggerReset(player);
        resetManager.displayResetMessage(player);
    } else if (playerChoice == 3) {
        cout << "You search the room carefully." << endl;
        cout << "You find a small mark on the wall: 314." << endl;
        cout << "Somehow, you feel like this number matters." << endl;

        player.setKnowsSecret(true);
    } else {
        cout << "Invalid choice. The room stays silent." << endl;
    }

    cout << endl;
    cout << "Deaths: " << player.getDeaths() << endl;

    if (player.getKnowsSecret()) {
        cout << "Remembered clue: 314" << endl;
    }
}