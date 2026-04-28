#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include <string>
#include <vector>

using namespace std;

/*
Stores the player's long-term memory and temporary progress
Memories stay after death, but temporary progress is reset
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

    bool ventilationActive;

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

    bool getVentilationActive() const;

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

    void setVentilationActive(bool value);

    void addMemory(string memory);
    vector<string> getMemoryLog() const;

    void resetForNewRun();
};

#endif