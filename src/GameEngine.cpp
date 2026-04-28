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
    cout << "              " << title << endl;
    cout << "========================================" << endl;
}

void printDeathHeader() {
    cout << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    cout << "                 YOU DIED" << endl;
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}

map<int, Scene> GameEngine::buildScenes() {
    map<int, Scene> scenes;

    Scene entrance(
        1,
        "You wake up in a dark room.\n"
        "The same cold floor. The same locked door.\n"
        "Nobody around you, just silence.\n"
        "Every reset brings you back here."
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
    threeDoors.addChoice(Choice("Open the right door.", 13));
    threeDoors.addChoice(Choice("Go back.", 1));
    threeDoors.addChoice(Choice("Exit game.", 0));

    Scene searchRoom(
        4,
        "You search the entrance room carefully.\n"
        "Behind a loose brick, you find a scratched message:\n"
        "CODE: 314"
    );
    searchRoom.addChoice(Choice("Return to the entrance.", 1));
    searchRoom.addChoice(Choice("Exit game.", 0));

    Scene patternHallway(
        5,
        "You enter a hallway covered with pressure plates.\n"
        "The plates are old, but some of them still look active.\n"
        "One wrong step could be deadly."
    );
    patternHallway.addChoice(Choice("Cross the pressure plates.", 99));
    patternHallway.addChoice(Choice("Step onto the plates without thinking.", 93));
    patternHallway.addChoice(Choice("Go back to the observation room.", 13));
    patternHallway.addChoice(Choice("Exit game.", 0));

    Scene mirrorRoom(
        6,
        "You enter a room filled with broken mirrors.\n"
        "On the wall, a word is written backwards: NEPO.\n"
        "It looks like the room is trying to tell you something."
    );
    mirrorRoom.addChoice(Choice("Study the backwards word.", 7));
    mirrorRoom.addChoice(Choice("Touch the largest mirror.", 94));
    mirrorRoom.addChoice(Choice("Go back.", 5));
    mirrorRoom.addChoice(Choice("Exit game.", 0));

    Scene ventilationRoom(
        7,
        "You find a small control room.\n"
        "There is a switch labeled VENTILATION.\n"
        "A warning says: GAS LEAK IN LOWER ROOM.\n"
        "On the floor, there is also a metal trapdoor that leads downward."
    );
    ventilationRoom.addChoice(Choice("Turn on the ventilation switch and open the trapdoor.", 100));
    ventilationRoom.addChoice(Choice("Ignore the switch and open the trapdoor.", 95));
    ventilationRoom.addChoice(Choice("Go back.", 6));
    ventilationRoom.addChoice(Choice("Exit game.", 0));

    Scene gasRoom(
        8,
        "You climb down through the metal trapdoor.\n"
        "The lower room is filled with pipes and green fog.\n"
        "Because the ventilation is running, the gas starts clearing."
    );
    gasRoom.addChoice(Choice("Walk through the lower room.", 9));
    gasRoom.addChoice(Choice("Go back up the trapdoor.", 7));
    gasRoom.addChoice(Choice("Exit game.", 0));

    Scene fakeExit(
        9,
        "You see a bright exit sign.\n"
        "For a moment, it looks like freedom.\n"
        "But something about it feels too easy."
    );
    fakeExit.addChoice(Choice("Run toward the bright exit.", 96));
    fakeExit.addChoice(Choice("Avoid the bright exit and look for another way.", 11));
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
    finalDoor.addChoice(Choice("Say the word OPEN.", 12));
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
        "A note under the screen says:\n"
        "SAFE STEPS: LEFT, RIGHT, FORWARD."
    );
    observationRoom.addChoice(Choice("Memorize the safe step pattern.", 5));
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

void GameEngine::showPlayerMemory(const PlayerState& player) const {
    cout << endl;
    cout << "Current loop status" << endl;
    cout << "Deaths: " << player.getDeaths() << endl;

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

void GameEngine::handleDeath(PlayerState& player, ResetManager& resetManager, string deathMessage, string memoryGained) {
    printDeathHeader();

    cout << deathMessage << endl;

    player.addMemory(memoryGained);
    resetManager.triggerReset(player);
    resetManager.displayResetMessage(player, memoryGained);
}

void GameEngine::start() {
    PlayerState player;
    ResetManager resetManager;
    map<int, Scene> scenes = buildScenes();
    stack<int> sceneHistory;

    int currentSceneId = 1;

    printSceneHeader("RESET");
    cout << "A Text Adventure Game" << endl;
    cout << "Learn. Die. Remember. Escape." << endl;

    while (!player.getGameOver()) {
        if (currentSceneId == 0) {
            player.setGameOver(true);
            printDivider();
            cout << "You chose to leave the loop for now." << endl;
            break;
        }

        // Special action: random keypad code.
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

        // Special action: left door death.
        if (currentSceneId == 91) {
            player.unlockLeftDoorDeath();

            handleDeath(
                player,
                resetManager,
                "The left door opens into a room with no floor.\n"
                "You step forward and fall into darkness.",
                "The left door kills you."
            );

            if (player.knowsLeftDoorDeath() && player.knowsFrontDoorDeath()) {
                player.unlockSafeDoor();
            }

            currentSceneId = 1;
            continue;
        }

        // Special action: front door death.
        if (currentSceneId == 92) {
            player.unlockFrontDoorDeath();

            handleDeath(
                player,
                resetManager,
                "You step through the front door.\n"
                "Metal spikes shoot out from both walls.",
                "The front door kills you."
            );

            if (player.knowsLeftDoorDeath() && player.knowsFrontDoorDeath()) {
                player.unlockSafeDoor();
            }

            currentSceneId = 1;
            continue;
        }

        // Special action: careless pressure plate death.
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

        // Special action: mirror death.
        if (currentSceneId == 94) {
            player.unlockMirrorWord();

            handleDeath(
                player,
                resetManager,
                "You touch the largest mirror.\n"
                "Your reflection grabs your hand and pulls you through the glass.",
                "The mirror word is OPEN."
            );
            currentSceneId = 1;
            continue;
        }

        // Special action: gas death.
        if (currentSceneId == 95) {
            player.unlockGasSwitch();

            handleDeath(
                player,
                resetManager,
                "You open the trapdoor without turning on the ventilation.\n"
                "The lower room is full of gas.\n"
                "You breathe once, then collapse.",
                "Turn on ventilation before entering the gas room."
            );
            currentSceneId = 1;
            continue;
        }

        // Special action: fake exit death.
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

        // Special action: forcing final door.
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

        // Special action: enter remembered code.
        if (currentSceneId == 98) {
            if (player.knowsDoorCode()) {
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

        // Special action: cross pressure plates.
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
                    "You try to cross the pressure plates without knowing the safe steps.\n"
                    "The plates sink under your feet and the ceiling falls.",
                    "Find the pattern before crossing the pressure plates."
                );
                currentSceneId = 1;
            }

            continue;
        }

        // Special action: turn on ventilation and enter gas room.
        if (currentSceneId == 100) {
            player.unlockGasSwitch();

            cout << endl;
            cout << "You turn on the ventilation switch." << endl;
            cout << "The pipes start shaking, and the green gas begins to clear." << endl;
            cout << "You open the trapdoor and climb down." << endl;

            currentSceneId = 8;
            continue;
        }

        // Special action: hidden hatch from control room.
        if (currentSceneId == 101) {
            if (player.knowsGasSwitch()) {
                cout << endl;
                cout << "You open the hidden floor hatch." << endl;
                cout << "Because you remember the ventilation system, you avoid the gas trap." << endl;
                currentSceneId = 8;
            } else {
                handleDeath(
                    player,
                    resetManager,
                    "You open the hidden floor hatch without checking the air below.\n"
                    "Gas rises from the lower room and fills your lungs.",
                    "The lower hatch is dangerous without ventilation."
                );
                currentSceneId = 1;
            }

            continue;
        }

        // Safety check in case the program ever points to a scene that does not exist.
        if (scenes.find(currentSceneId) == scenes.end()) {
            cout << "Error: Scene " << currentSceneId << " does not exist." << endl;
            player.setGameOver(true);
            break;
        }

        Scene currentScene = scenes[currentSceneId];

        printSceneHeader("SCENE " + to_string(currentSceneId));
        currentScene.displayScene();

        if (currentSceneId == 4) {
            player.unlockDoorCode();
            cout << "Memory unlocked: Door code 314" << endl;
        }

        if (currentSceneId == 6) {
            player.unlockMirrorWord();
            cout << "Memory unlocked: Mirror word OPEN" << endl;
        }

        if (currentSceneId == 13) {
            player.unlockHallwayPattern();
            cout << "Memory unlocked: Hallway pattern: left, right, forward." << endl;
        }

        if (currentSceneId == 12) {
            if (
                player.knowsDoorCode() &&
                player.knowsSafeDoor() &&
                player.knowsHallwayPattern() &&
                player.knowsMirrorWord() &&
                player.knowsGasSwitch() &&
                player.knowsFakeExit()
            ) {
                player.setTrueEndingReached(true);
                player.setGameOver(true);

                printSceneHeader("TRUE ENDING");
                cout << "You escaped after learning from every reset." << endl;
                showPlayerMemory(player);
                break;
            } else {
                handleDeath(
                    player,
                    resetManager,
                    "You reach the final door, but you do not understand the loop yet.\n"
                    "The door stays shut and the room resets.",
                    "You need more memories before escaping."
                );
                currentSceneId = 1;
                continue;
            }
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