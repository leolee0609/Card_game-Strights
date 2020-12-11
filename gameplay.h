#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <string>
#include <vector>
#include "player.h"
#include <random>
#include <algorithm>
#include <sstream>

class Gameplay : public Observer {
    protected:
    std::default_random_engine dre;
    std::vector<std::string> deck;
    std::vector<Player *> players;
    std::vector<std::string> clubs;
    std::vector<std::string> diamonds;
    std::vector<std::string> hearts;
    std::vector<std::string> spades;
    std::vector<int> winPlayers;

    virtual void recalculate() = 0;
    virtual void printGame(Player * thePlayer) = 0;
    virtual bool ifEnd() = 0;
    virtual void printScoring() = 0;
    virtual Player * findfirst() = 0;
    virtual Player * gotoNext(Player * current) = 0;

    public:
    virtual void notify( Subject & whoNotified ) override;
    void setDeck(std::vector<std::string> & theDeck);
    void setRandom(std::default_random_engine theDre);
    void addPlayer(Player * newplayer);
    void reshuffle();
    void getCard();
    void proceed();
    void returnCard();
    virtual bool gameOver() = 0;      // returns true is the game should over and emplace back the numbers for winning players
};

#endif

