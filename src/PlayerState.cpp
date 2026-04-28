#include "PlayerState.h"

PlayerState::PlayerState() {
    deaths = 0;
    gameOver = false;
    trueEndingReached = false;

    remembersDoorCode = false;
    remembersLeftDoorDeath = false;
    remembersFrontDoorDeath = false;
    remembersSafeDoor = false;
    remembersHallwayPattern = false;
    remembersMirrorWord = false;
    remembersGasSwitch = false;
    remembersFakeExit = false;

    ventilationActive = false;
}

int PlayerState::getDeaths() const {
    return deaths;
}

bool PlayerState::getGameOver() const {
    return gameOver;
}

bool PlayerState::getTrueEndingReached() const {
    return trueEndingReached;
}

bool PlayerState::knowsDoorCode() const {
    return remembersDoorCode;
}

bool PlayerState::knowsLeftDoorDeath() const {
    return remembersLeftDoorDeath;
}

bool PlayerState::knowsFrontDoorDeath() const {
    return remembersFrontDoorDeath;
}

bool PlayerState::knowsSafeDoor() const {
    return remembersSafeDoor;
}

bool PlayerState::knowsHallwayPattern() const {
    return remembersHallwayPattern;
}

bool PlayerState::knowsMirrorWord() const {
    return remembersMirrorWord;
}

bool PlayerState::knowsGasSwitch() const {
    return remembersGasSwitch;
}

bool PlayerState::knowsFakeExit() const {
    return remembersFakeExit;
}

bool PlayerState::getVentilationActive() const {
    return ventilationActive;
}

void PlayerState::addDeath() {
    deaths++;
}

void PlayerState::setGameOver(bool value) {
    gameOver = value;
}

void PlayerState::setTrueEndingReached(bool value) {
    trueEndingReached = value;
}

void PlayerState::unlockDoorCode() {
    remembersDoorCode = true;
    addMemory("Door code: 314729");
}

void PlayerState::unlockLeftDoorDeath() {
    remembersLeftDoorDeath = true;
    addMemory("The left door kills you.");
}

void PlayerState::unlockFrontDoorDeath() {
    remembersFrontDoorDeath = true;
    addMemory("The front door kills you.");
}

void PlayerState::unlockSafeDoor() {
    remembersSafeDoor = true;
    addMemory("Apparently, the right door is the safe one.");
}

void PlayerState::unlockHallwayPattern() {
    remembersHallwayPattern = true;
    addMemory("Hallway pattern: left, right, forward.");
}

void PlayerState::unlockMirrorWord() {
    remembersMirrorWord = true;
    addMemory("Mirror word: OPEN");
}

void PlayerState::unlockGasSwitch() {
    remembersGasSwitch = true;
    addMemory("Ventilation must be turned on before entering the gas room.");
}

void PlayerState::unlockFakeExit() {
    remembersFakeExit = true;
    addMemory("The bright exit is fake.");
}

void PlayerState::setVentilationActive(bool value) {
    ventilationActive = value;
}

void PlayerState::addMemory(string memory) {
    if (memory == "") {
        return;
    }

    for (int i = 0; i < memoryLog.size(); i++) {
        if (memoryLog[i] == memory) {
            return;
        }
    }

    memoryLog.push_back(memory);
}

vector<string> PlayerState::getMemoryLog() const {
    return memoryLog;
}

void PlayerState::resetForNewRun() {
    gameOver = false;
    ventilationActive = false;
}