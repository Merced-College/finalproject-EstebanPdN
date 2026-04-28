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

map<int, Scene> GameEngine::buildScenes() {
    map<int, Scene> scenes;

    Scene entrance(
        1,
        "You wake up in a dark room.\n"
        "The same cold floor. The same locked door. The same silence.\n"
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
        "The keypad is waiting for a three-digit code."
    );
    lockedDoor.addChoice(Choice("Enter a code.", 10));
    lockedDoor.addChoice(Choice("Press random numbers.", 90));
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
    patternHallway.addChoice(Choice("Step onto the plates without a plan.", 93));
    patternHallway.addChoice(Choice("Follow the pattern you remember.", 6));
    patternHallway.addChoice(Choice("Go back to the observation room.", 13));
    patternHallway.addChoice(Choice("Exit game.", 0));

    Scene mirrorRoom(
        6,
        "You enter a room filled with broken mirrors.\n"
        "On the wall, a word is written backwards: NEPO.\n"
        "It looks like the room is trying to tell you something."
    );
    mirrorRoom.addChoice(Choice("Remember the mirror word.", 7));
    mirrorRoom.addChoice(Choice("Touch the largest mirror.", 94));
    mirrorRoom.addChoice(Choice("Go back.", 5));
    mirrorRoom.addChoice(Choice("Exit game.", 0));

    Scene ventilationRoom(
        7,
        "You find a small control room.\n"
        "There is a switch labeled VENTILATION.\n"
        "A warning says: GAS LEAK IN LOWER ROOM."
    );
    ventilationRoom.addChoice(Choice("Turn on the ventilation switch.", 8));
    ventilationRoom.addChoice(Choice("Ignore the switch and continue.", 95));
    ventilationRoom.addChoice(Choice("Go back.", 6));
    ventilationRoom.addChoice(Choice("Exit game.", 0));

    Scene gasRoom(
        8,
        "You enter the lower room.\n"
        "A green fog covers the floor.\n"
        "If the ventilation is off, this room is deadly."
    );
    gasRoom.addChoice(Choice("Walk through the gas room.", 9));
    gasRoom.addChoice(Choice("Go back.", 7));
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
        "A monitor says: Knowledge survives the reset."
    );
    controlRoom.addChoice(Choice("Return to the entrance.", 1));
    controlRoom.addChoice(Choice("Open the hidden lower passage.", 8));
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
    observationRoom.addChoice(Choice("Remember the safe step pattern.", 5));
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
    cout << endl;
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

    cout << "==============================" << endl;
    cout << "RESET - A Text Adventure Game" << endl;
    cout << "==============================" << endl;
    cout << endl;

    while (!player.getGameOver()) {
        if (currentSceneId == 0) {
            player.setGameOver(true);
            cout << endl;
            cout << "You chose to leave the loop for now." << endl;
            break;
        }

        if (currentSceneId == 90) {
            handleDeath(player, resetManager, "The keypad shocks you instantly.", "Random keypad numbers are dangerous.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 91) {
            player.unlockLeftDoorDeath();

            if (player.knowsLeftDoorDeath() && player.knowsFrontDoorDeath()) {
                player.unlockSafeDoor();
            }

            handleDeath(player, resetManager, "The left door opens into a room with no floor. You fall.", "The left door kills you.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 92) {
            player.unlockFrontDoorDeath();

            if (player.knowsLeftDoorDeath() && player.knowsFrontDoorDeath()) {
                player.unlockSafeDoor();
            }

            handleDeath(player, resetManager, "You step through the front door and metal spikes shoot from the wall.", "The front door kills you.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 93) {
            handleDeath(player, resetManager, "You step on the wrong pressure plate. The hallway collapses.", "Do not cross the pressure plates without the safe pattern.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 94) {
            player.unlockMirrorWord();
            handleDeath(player, resetManager, "The mirror pulls you in and everything turns black.", "The mirror word is OPEN.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 95) {
            player.unlockGasSwitch();
            handleDeath(player, resetManager, "You ignore the switch. The lower room fills with gas and you collapse.", "Turn on ventilation before entering the gas room.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 96) {
            player.unlockFakeExit();
            handleDeath(player, resetManager, "You run toward the bright exit, but it is only a trap.", "The bright exit is fake.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 97) {
            handleDeath(player, resetManager, "You force the final door. The loop rejects you.", "The final door opens only with the word OPEN.");
            currentSceneId = 1;
            continue;
        }

        Scene currentScene = scenes[currentSceneId];

        cout << endl;
        currentScene.displayScene();

        if (currentSceneId == 4) {
            player.unlockDoorCode();
            cout << "Memory unlocked: Door code 314" << endl;
        }

        if (currentSceneId == 6) {
            player.unlockMirrorWord();
            cout << "Memory unlocked: Mirror word OPEN" << endl;
        }

        if (currentSceneId == 8 && !player.knowsGasSwitch()) {
            handleDeath(player, resetManager, "You enter the gas room without knowing about the ventilation switch. You collapse.", "The gas room needs ventilation first.");
            currentSceneId = 1;
            continue;
        }

        if (currentSceneId == 10 && !player.knowsDoorCode()) {
            handleDeath(player, resetManager, "You enter a code without actually knowing it. The keypad rejects you.", "Find the code before using the keypad.");
            currentSceneId = 1;
            continue;
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

                cout << endl;
                cout << "TRUE ENDING REACHED" << endl;
                cout << "You escaped after learning from every reset." << endl;
                showPlayerMemory(player);
                break;
            } else {
                handleDeath(player, resetManager, "You reach the final door, but you do not understand the loop yet.", "You need more memories before escaping.");
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

        if (currentSceneId == 5 && playerChoice == 2 && !player.knowsHallwayPattern()) {
            handleDeath(player, resetManager, "You try to follow a pattern you never learned. The floor collapses.", "Find the pattern before crossing the pressure plates.");
            currentSceneId = 1;
            continue;
        }

        sceneHistory.push(currentSceneId);
        currentSceneId = choices[playerChoice - 1].getNextSceneId();
    }

    cout << endl;
    cout << "Game finished." << endl;
}