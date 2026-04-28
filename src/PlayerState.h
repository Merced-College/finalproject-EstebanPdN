#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <string>
#include <vector>

using namespace std;

/*
Author: Esteban Pereira das Neves
Class: PlayerState

Description:
Stores the player's long-term memory and game progress.
Temporary progress is lost after death, but memories remain.
*/

class PlayerState {
private:
    int deaths;
    bool gameOver;
    bool trueEndingReached;

    bool remembersDoorCode;
    bool remembersLeftDoorDeath;
    bool remembersFrontDoorDeath;
    bool remembersSafeDoor;
    bool remembersHallwayPattern;
    bool remembersMirrorWord;
    bool remembersGasSwitch;
    bool remembersFakeExit;

    vector<string> memoryLog;

public:
    PlayerState();

    int getDeaths() const;
    bool getGameOver() const;
    bool getTrueEndingReached() const;

    bool knowsDoorCode() const;
    bool knowsLeftDoorDeath() const;
    bool knowsFrontDoorDeath() const;
    bool knowsSafeDoor() const;
    bool knowsHallwayPattern() const;
    bool knowsMirrorWord() const;
    bool knowsGasSwitch() const;
    bool knowsFakeExit() const;

    void addDeath();
    void setGameOver(bool value);
    void setTrueEndingReached(bool value);

    void unlockDoorCode();
    void unlockLeftDoorDeath();
    void unlockFrontDoorDeath();
    void unlockSafeDoor();
    void unlockHallwayPattern();
    void unlockMirrorWord();
    void unlockGasSwitch();
    void unlockFakeExit();

    void addMemory(string memory);
    vector<string> getMemoryLog() const;

    void resetForNewRun();
};

#endif