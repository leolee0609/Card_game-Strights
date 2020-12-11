#ifndef CARD_H
#define CARD_H
#include "subject.h"
#include <sstream>
#include <string.h>
#include <iostream>

class Card : public Subject {
    const char suit; // C, D, H, or S
    const char rank;  // A~K
    bool islegal;
    std::string status;     // either in hand (default), played, or discarded

    public:
    // constructors
    explicit Card(char suit, char rank);
    Card(const Card & other);
    Card (Card && other);
    // destructor
    ~Card();
    // accessors
    char getSuit() const;
    int getRank() const;
    bool getIslegal() const;
    std::string getStatus() const;
    // mutators
    void setIslegal(bool b);

    void beplayed();
    void bediscarded();
    virtual std::pair<char, int> getInfo() const override;
    char getRankChar() const;
};


#endif
