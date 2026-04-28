#include "PlayerState.h"

PlayerState::PlayerState() {
    deaths = 0;
    hasKey = false;
    knowsSecret = false;
    gameOver = false;
    trueEndingReached = false;
}

int PlayerState::getDeaths() const {
    return deaths;
}

bool PlayerState::getHasKey() const {
    return hasKey;
}

bool PlayerState::getKnowsSecret() const {
    return knowsSecret;
}

bool PlayerState::getGameOver() const {
    return gameOver;
}

bool PlayerState::getTrueEndingReached() const {
    return trueEndingReached;
}

void PlayerState::addDeath() {
    deaths++;
}

void PlayerState::setHasKey(bool value) {
    hasKey = value;
}

void PlayerState::setKnowsSecret(bool value) {
    knowsSecret = value;
}

void PlayerState::setGameOver(bool value) {
    gameOver = value;
}

void PlayerState::setTrueEndingReached(bool value) {
    trueEndingReached = value;
}

void PlayerState::resetForNewRun() {
    hasKey = false;
    gameOver = false;
}