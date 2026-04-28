#include <iostream>
#include "GameEngine.h"
#include "Scene.h"
#include "Choice.h"
#include "PlayerState.h"

using namespace std;

void GameEngine::start() {
    cout << "==============================" << endl;
    cout << "RESET - A Text Adventure Game" << endl;
    cout << "==============================" << endl;
    cout << endl;

    PlayerState player;

    cout << "Deaths so far: " << player.getDeaths() << endl;
    cout << endl;

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

    cout << "For now, the game displays the first scene and the player state." << endl;
}