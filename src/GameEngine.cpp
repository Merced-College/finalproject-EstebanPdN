#include <iostream>
#include <map>
#include <stack>
#include <limits>
#include "GameEngine.h"
#include "Scene.h"
#include "Choice.h"
#include "PlayerState.h"
#include "ResetManager.h"

using namespace std;

void printDivider() {
    cout << endl;
    cout << "----------------------------------------" << endl;
}

void printSceneHeader(string title) {
    cout << endl;
    cout << "========================================" << endl;
    cout << "          " << title << endl;
    cout << "========================================" << endl;
}

void printDeathHeader() {
    cout << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "                 YOU DIED" << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}

void printWakeUpText() {
    cout << endl;
    cout << "You wake up in a dark room." << endl;
    cout << "The same cold floor. The same locked door." << endl;
    cout << "Nobody around you, just silence." << endl;
    cout << "Every reset brings you back here." << endl;
}

/*
Scene Setup

This function creates all of the rooms in the game and stores them
inside a map using scene ID numbers. Each scene has a description
and a list of choices that point to the next scene or special action.

*/
map<int, Scene> GameEngine::buildScenes() {
    map<int, Scene> scenes;

    Scene entrance(
        1,
        "This is an empty room.\n"
        "There are several ways forward, but no clear way out."
    );
    entrance.addChoice(Choice("Go to the locked door.", 2));
    entrance.addChoice(Choice("Enter the hallway with three doors.", 3));
    entrance.addChoice(Choice("Search the room.", 4));
    entrance.addChoice(Choice("Exit game.", 0));

    Scene lockedDoor(
        2,
        "You stand in front of the locked door.\n"
        "There is a keypad beside it.\n"
        "A warning is scratched into the wall:\n"
        "WRONG CODE = DETONATION."
    );
    lockedDoor.addChoice(Choice("Enter the code you remember.", 98));
    lockedDoor.addChoice(Choice("Try a random code.", 90));
    lockedDoor.addChoice(Choice("Go back.", 1));
    lockedDoor.addChoice(Choice("Exit game.", 0));

    Scene threeDoors(
        3,
        "You enter a hallway with three doors.\n"
        "One door is on the left, one is straight ahead, and one is on the right.\n"
        "They all look almost the same."
    );
    threeDoors.addChoice(Choice("Open the left door.", 91));
    threeDoors.addChoice(Choice("Open the front door.", 92));
    threeDoors.addChoice(Choice("Open the right door.", 107));
    threeDoors.addChoice(Choice("Go back.", 1));
    threeDoors.addChoice(Choice("Exit game.", 0));

    Scene searchRoom(
        4,
        "You search the entrance room carefully.\n"
        "Behind a loose brick, you find a scratched message:\n"
        "CODE: 314729"
    );
    searchRoom.addChoice(Choice("Memorize the code and return.", 102));
    searchRoom.addChoice(Choice("Return without studying it.", 1));
    searchRoom.addChoice(Choice("Exit game.", 0));

    Scene patternHallway(
        5,
        "You enter a hallway covered with pressure plates.\n"
        "The plates are old, but some of them still look active.\n"
        "One wrong step could be deadly."
    );
    patternHallway.addChoice(Choice("Cross the pressure plates using a pattern.", 99));
    patternHallway.addChoice(Choice("Step onto the plates without thinking.", 93));
    patternHallway.addChoice(Choice("Go back to the observation room.", 13));
    patternHallway.addChoice(Choice("Exit game.", 0));

    Scene mirrorRoom(
        6,
        "You enter a room filled with broken mirrors.\n"
        "On the wall, a word is written backwards: NEPO.\n"
        "It looks like the room is trying to tell you something."
    );
    mirrorRoom.addChoice(Choice("Study the backwards word.", 103));
    mirrorRoom.addChoice(Choice("Touch the largest mirror.", 94));
    mirrorRoom.addChoice(Choice("Go back.", 5));
    mirrorRoom.addChoice(Choice("Exit game.", 0));

    Scene ventilationRoom(
        7,
        "You find a small control room.\n"
        "There is a yellow button and a blue button on the wall.\n"
        "A warning sign says: GAS SYSTEM CONTROL.\n"
        "Near the corner, you notice a hole in the floor."
    );
    ventilationRoom.addChoice(Choice("Press the yellow button.", 100));
    ventilationRoom.addChoice(Choice("Press the blue button.", 108));
    ventilationRoom.addChoice(Choice("Crawl through the hole in the floor.", 109));
    ventilationRoom.addChoice(Choice("Go back.", 6));
    ventilationRoom.addChoice(Choice("Exit game.", 0));

    Scene gasRoom(
        8,
        "You climb down through the hidden floor hatch.\n"
        "The lower room is filled with pipes and green fog.\n"
        "Because the ventilation is running, the gas starts clearing."
    );
    gasRoom.addChoice(Choice("Walk through the lower room.", 9));
    gasRoom.addChoice(Choice("Go back up the hatch.", 10));
    gasRoom.addChoice(Choice("Exit game.", 0));

    Scene fakeExit(
        9,
        "You see a bright exit sign.\n"
        "For a moment, it looks like freedom.\n"
        "But something about it feels too easy."
    );
    fakeExit.addChoice(Choice("Run toward the bright exit.", 96));
    fakeExit.addChoice(Choice("Avoid the bright exit and look for another way.", 104));
    fakeExit.addChoice(Choice("Exit game.", 0));

    Scene controlRoom(
        10,
        "The keypad accepts the code.\n"
        "The locked door opens and reveals a control room.\n"
        "A monitor says: Knowledge survives the reset.\n"
        "Under the monitor, you notice a hidden floor hatch leading downward."
    );
    controlRoom.addChoice(Choice("Return to the entrance.", 1));
    controlRoom.addChoice(Choice("Open the hidden floor hatch.", 101));
    controlRoom.addChoice(Choice("Exit game.", 0));

    Scene finalDoor(
        11,
        "Behind the fake exit, you find a smaller door.\n"
        "It has no handle.\n"
        "Only one word is carved into it: OPEN."
    );
    finalDoor.addChoice(Choice("Say the word OPEN.", 105));
    finalDoor.addChoice(Choice("Force the door open.", 97));
    finalDoor.addChoice(Choice("Exit game.", 0));

    Scene trueEnding(
        12,
        "The door opens quietly.\n"
        "For the first time, the room does not reset.\n"
        "You step outside.\n"
        "The loop is finally broken."
    );

    Scene observationRoom(
        13,
        "The right door leads into a small observation room.\n"
        "Old security monitors cover the wall.\n"
        "One screen shows a hallway with pressure plates.\n"
        "There might be something useful in this room."
    );
    observationRoom.addChoice(Choice("Search the observation room.", 106));
    observationRoom.addChoice(Choice("Go through the next door.", 5));
    observationRoom.addChoice(Choice("Go back to the three-door hallway.", 3));
    observationRoom.addChoice(Choice("Exit game.", 0));

    scenes[1] = entrance;
    scenes[2] = lockedDoor;
    scenes[3] = threeDoors;
    scenes[4] = searchRoom;
    scenes[5] = patternHallway;
    scenes[6] = mirrorRoom;
    scenes[7] = ventilationRoom;
    scenes[8] = gasRoom;
    scenes[9] = fakeExit;
    scenes[10] = controlRoom;
    scenes[11] = finalDoor;
    scenes[12] = trueEnding;
    scenes[13] = observationRoom;

    return scenes;
}

string GameEngine::getSceneName(int sceneId) const {
    if (sceneId == 1) {
        return "ENTRANCE ROOM";
    } else if (sceneId == 2) {
        return "LOCKED DOOR";
    } else if (sceneId == 3) {
        return "THREE-DOOR HALLWAY";
    } else if (sceneId == 4) {
        return "SEARCHED ENTRANCE ROOM";
    } else if (sceneId == 5) {
        return "PRESSURE PLATE HALLWAY";
    } else if (sceneId == 6) {
        return "MIRROR ROOM";
    } else if (sceneId == 7) {
        return "VENTILATION ROOM";
    } else if (sceneId == 8) {
        return "GAS ROOM";
    } else if (sceneId == 9) {
        return "BRIGHT EXIT";
    } else if (sceneId == 10) {
        return "CONTROL ROOM";
    } else if (sceneId == 11) {
        return "FINAL DOOR";
    } else if (sceneId == 12) {
        return "YOU ESCAPED";
    } else if (sceneId == 13) {
        return "OBSERVATION ROOM";
    }

    return "UNKNOWN AREA";
}

void GameEngine::showPlayerMemory(const PlayerState& player) const {
    cout << endl;
    cout << "Current loop status" << endl;
    cout << "Deaths: " << player.getDeaths() << endl;

    if (player.getVentilationActive()) {
        cout << "Ventilation: active" << endl;
    } else {
        cout << "Ventilation: off" << endl;
    }

    vector<string> memories = player.getMemoryLog();

    if (memories.size() == 0) {
        cout << "Memories: none" << endl;
    } else {
        cout << "Memories:" << endl;

        for (int i = 0; i < memories.size(); i++) {
            cout << "- " << memories[i] << endl;
        }
    }

    cout << endl;
}

/*
Reset Memory System

This function handles what happens when the player dies. It prints
the death message, saves the memory gained from that mistake, increases
the death counter, and resets temporary progress for the next run.

The game is based on learning through resets.
The player loses temporary progress, like the position ot the active ventilation, but keeps
important memories, like the door code or which rooms are dangerous.

*/
void GameEngine::handleDeath(PlayerState& player, ResetManager& resetManager, string deathMessage, string memoryGained) {
    printDeathHeader();

    cout << deathMessage << endl;

    player.addMemory(memoryGained);
    resetManager.triggerReset(player);
    resetManager.displayResetMessage(player, memoryGained);
}

/*
Main Game Loop and Action Validation

This function runs the main game loop. It displays the current room,
shows the player's memories, gets the player's input, and moves the
player to the next scene.

Some choices are special actions instead of normal scenes. These actions
are checked before the player moves forward.
*/

void GameEngine::start() {
    PlayerState player;
    ResetManager resetManager;
    map<int, Scene> scenes = buildScenes();
    stack<int> sceneHistory;

    int currentSceneId = 1;

    printSceneHeader("RESET");
    cout << "A Text Adventure Game" << endl;
    cout << "Learn. Die. Remember. Escape." << endl;

    printWakeUpText();

    while (!player.getGameOver()) {
        if (currentSceneId == 0) {
            player.setGameOver(true);
            printDivider();
            cout << "You chose to leave the loop for now." << endl;
            break;
        }

        if (currentSceneId == 90) {
            handleDeath(
                player,
                resetManager,
                "You press random numbers on the keypad.\n"
                "For one second, everything is silent.\n"
                "Then the door clicks, a red light turns on, and a hidden bomb explodes.",
                "Random keypad codes trigger a bomb."
            );
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 91) {
            player.unlockLeftDoorDeath();

            handleDeath(
                player,
                resetManager,
                "The left door opens into a room with no floor.\n"
                "You step forward and fall into darkness.",
                "The left door kills you."
            );

            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 92) {
            player.unlockFrontDoorDeath();

            handleDeath(
                player,
                resetManager,
                "You step through the front door.\n"
                "Metal spikes shoot out from both walls.",
                "The front door kills you."
            );

            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 93) {
            handleDeath(
                player,
                resetManager,
                "You step onto the pressure plates without thinking.\n"
                "The floor collapses under you.",
                "Do not cross the pressure plates without the safe pattern."
            );
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 94) {
            handleDeath(
                player,
                resetManager,
                "You touch the largest mirror.\n"
                "Your reflection grabs your hand and pulls you through the glass.",
                "Do not touch the largest mirror."
            );
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 95) {
            handleDeath(
                player,
                resetManager,
                "You open the hatch without ventilation.\n"
                "The lower room is full of gas.\n"
                "You breathe once, then collapse.",
                "Ventilation must be turned on before entering the gas room."
            );
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 96) {
            player.unlockFakeExit();

            handleDeath(
                player,
                resetManager,
                "You run toward the bright exit.\n"
                "The sign flickers and disappears.\n"
                "The floor opens beneath you.",
                "The bright exit is fake."
            );
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 97) {
            handleDeath(
                player,
                resetManager,
                "You try to force the final door open.\n"
                "The carved word begins to glow.\n"
                "The loop rejects you and crushes the room around you.",
                "The final door opens only with the word OPEN."
            );
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 98) {
            if (player.knowsDoorCode()) {
                cout << endl;
                cout << "You enter the remembered code: 314729." << endl;
                cout << "The keypad turns green." << endl;
                currentSceneId = 10;
            } else {
                handleDeath(
                    player,
                    resetManager,
                    "You try to enter a code you never actually learned.\n"
                    "The keypad detects the wrong attempt.\n"
                    "A bomb inside the door explodes.",
                    "Find the code before using the keypad."
                );
                currentSceneId = 1;
            }

            continue;
        }

        if (currentSceneId == 99) {
            if (player.knowsHallwayPattern()) {
                cout << endl;
                cout << "You follow the remembered pattern: left, right, forward." << endl;
                cout << "The pressure plates click, but nothing collapses." << endl;
                currentSceneId = 6;
            } else {
                handleDeath(
                    player,
                    resetManager,
                    "You try to cross the pressure plates using a pattern,\n"
                    "but you never learned the correct order.\n"
                    "The plates sink under your feet and the ceiling falls.",
                    "Find the pattern before crossing the pressure plates."
                );
                currentSceneId = 1;
            }

            continue;
        }

        if (currentSceneId == 100) {
            player.unlockGasSwitch();
            player.setVentilationActive(true);

            cout << endl;
            cout << "You press the yellow button." << endl;
            cout << "The ventilation system is now running." << endl;
            cout << "The gas below should be clearing." << endl;
            cout << "Memory unlocked: Ventilation must be turned on before entering the gas room." << endl;

            currentSceneId = 7;
            continue;
        }

        if (currentSceneId == 101) {
            if (player.getVentilationActive()) {
                cout << endl;
                cout << "You open the hidden floor hatch." << endl;
                cout << "Because the ventilation is active right now, the gas trap is cleared." << endl;
                currentSceneId = 8;
            } else {
                handleDeath(
                    player,
                    resetManager,
                    "You open the hidden floor hatch without active ventilation.\n"
                    "Gas rises from the lower room and fills your lungs.",
                    "Ventilation must be turned on before entering the gas room."
                );
                currentSceneId = 1;
            }

            continue;
        }

        if (currentSceneId == 102) {
            player.unlockDoorCode();

            cout << endl;
            cout << "You study the scratched message carefully." << endl;
            cout << "Memory unlocked: Door code 314729" << endl;

            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 103) {
            player.unlockMirrorWord();

            cout << endl;
            cout << "You study the backwards word: NEPO." << endl;
            cout << "In the mirror, it reads: OPEN." << endl;
            cout << "Memory unlocked: Mirror word OPEN" << endl;

            currentSceneId = 7;
            continue;
        }

        if (currentSceneId == 104) {
            player.unlockFakeExit();

            cout << endl;
            cout << "You stop before running toward the bright exit." << endl;
            cout << "The sign flickers for a second, almost like a trap." << endl;
            cout << "Memory unlocked: The bright exit is fake." << endl;

            currentSceneId = 11;
            continue;
        }

        if (currentSceneId == 105) {
            if (
                player.knowsDoorCode() &&
                player.knowsSafeDoor() &&
                player.knowsHallwayPattern() &&
                player.knowsMirrorWord() &&
                player.knowsGasSwitch() &&
                player.knowsFakeExit()
            ) {
                currentSceneId = 12;
            } else {
                handleDeath(
                    player,
                    resetManager,
                    "You say OPEN, but the door does not move.\n"
                    "The loop is still stronger than you.\n"
                    "You do not understand everything yet.",
                    "You need more memories before escaping."
                );
                currentSceneId = 1;
            }

            continue;
        }

        if (currentSceneId == 106) {
            player.unlockHallwayPattern();

            cout << endl;
            cout << "You search the observation room carefully." << endl;
            cout << "One monitor shows the pressure plates from above." << endl;
            cout << "A note under the screen says: SAFE STEPS: LEFT, RIGHT, FORWARD." << endl;
            cout << "Memory unlocked: Hallway pattern: left, right, forward." << endl;

            currentSceneId = 13;
            continue;
        }

        if (currentSceneId == 107) {
            player.unlockSafeDoor();

            cout << endl;
            cout << "You open the right door." << endl;
            cout << "Nothing attacks you." << endl;
            cout << "Memory unlocked: Apparently, the right door is the safe one." << endl;

            currentSceneId = 13;
            continue;
        }

        if (currentSceneId == 108) {
            handleDeath(
                player,
                resetManager,
                "You press the blue button.\n"
                "A loud alarm starts ringing.\n"
                "Gas floods the building from the vents, and you collapse before reaching the door.",
                "Do not press the blue button."
            );
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 109) {
            if (player.getVentilationActive()) {
                cout << endl;
                cout << "You crawl through the hole in the floor." << endl;
                cout << "The narrow passage twists under the building." << endl;
                cout << "After a few moments, it leads you back to the entrance room." << endl;

                currentSceneId = 1;
            } else {
                handleDeath(
                    player,
                    resetManager,
                    "You crawl through the hole in the floor without active ventilation.\n"
                    "The tunnel below is filled with gas.\n"
                    "You try to turn back, but it is too late.",
                    "Ventilation must be turned on before entering the gas room."
                );
                currentSceneId = 1;
            }

            continue;
        }

        if (scenes.find(currentSceneId) == scenes.end()) {
            cout << "Error: Scene " << currentSceneId << " does not exist." << endl;
            player.setGameOver(true);
            break;
        }

        Scene currentScene = scenes[currentSceneId];

        printSceneHeader(getSceneName(currentSceneId));
        currentScene.displayScene();

        if (currentSceneId == 12) {
            player.setTrueEndingReached(true);
            player.setGameOver(true);

            cout << endl;
            cout << "You escaped after learning from every reset." << endl;
            showPlayerMemory(player);
            break;
        }

        showPlayerMemory(player);

        vector<Choice> choices = currentScene.getChoices();

        int playerChoice;
        cout << "Enter your choice: ";
        cin >> playerChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (playerChoice < 1 || playerChoice > choices.size()) {
            cout << "Invalid choice. Try again." << endl;
            continue;
        }

        sceneHistory.push(currentSceneId);
        currentSceneId = choices[playerChoice - 1].getNextSceneId();
    }

    printDivider();
    cout << "Game finished." << endl;
}