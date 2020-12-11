#ifndef PLAYER_H
#define PLAYER_H
#include "observer.h"
#include <algorithm>
#include <utility>
#include <vector>
#include <memory>
#include "card.h"
#include "computer.h"
#include <exception>
#include "human.h"
#include "computer.h"

class Player : public Observer{
    std::pair<char, int> currentPlayed;
    std::vector<std::string> deck;
    bool isHuman;
    int score;
    int baseScore;
    int no;
    Execution * exePolicy;

    public:
    void setDeck(const std::vector<std::string> & theDeck);
    void printDeck();
    int getNo() const;
    std::vector<Card> cards;
    Player(bool isHuman, int no);
    Player();
    Player(Player && other);
    Player(const Player & other);
    Player& operator=(const Player& other);
    virtual void notify( Subject & whoNotified ) override;
    void attachCard(Card newcard);
    void returnCard();
    void play(Card &playedcard);
    void discard(Card &discardedcard);
    void execute();
    void printCards();
    bool getIshuman() const;
    int getCurscore() const;
    int getScore() const;
    std::pair<char, int> getCurplayed() const;
    void combineScore();
    void setCurrentplayed(std::pair<char, int> curp);
    void clearDeck();
};

#endif
