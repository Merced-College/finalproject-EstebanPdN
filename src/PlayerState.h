#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

/*
Stores the player's progress and important flags

Stores some information that will stay remembered after 
the player dies or reaches a bad ending
*/

class PlayerState {
private:
    int deaths;
    bool hasKey;
    bool knowsSecret;
    bool gameOver;
    bool trueEndingReached;

public:
    PlayerState();

    int getDeaths() const;
    bool getHasKey() const;
    bool getKnowsSecret() const;
    bool getGameOver() const;
    bool getTrueEndingReached() const;

    void addDeath();
    void setHasKey(bool value);
    void setKnowsSecret(bool value);
    void setGameOver(bool value);
    void setTrueEndingReached(bool value);

    void resetForNewRun();
};

#endif