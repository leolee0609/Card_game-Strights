#include "card.h"


Card::Card(char suit, char rank) : suit{suit}, rank{rank}, islegal{false}, status{"in hand"} {}

Card::Card(const Card & other) : suit{other.suit}, rank{other.rank}, islegal{other.islegal}, status{other.status} {}

Card::Card (Card && other) : suit{other.suit}, rank{other.rank}, islegal{other.islegal}, status{other.status} {}

Card::~Card() {}

int Card::getRank() const {
    int ret;
    if (rank == 'A') {
        ret = 1;
    } else if (rank == 'J') {
        ret = 11;
    } else if (rank == 'Q') {
        ret = 12;
    } else if (rank == 'K') {
        ret = 13;
    } else if (rank == 'T') {
        ret = 10;
    } else {
        ret = rank - 48;
    }
    return ret;
}

char Card::getSuit() const {
    return suit;
}

bool Card::getIslegal() const {
    return islegal;
}

std::string Card::getStatus() const {
    return status;
}

void Card::setIslegal(bool b) {
    islegal = b;
}

void Card::beplayed() {
    status = "played";
    islegal = false;
    notifyObservers();
}

void Card::bediscarded() {
    status = "discarded";
    islegal = false;
}

std::pair<char, int> Card::getInfo() const {
    std::pair<char, int> information = std::make_pair(suit, getRank());
    return information;
}

char Card::getRankChar() const {
    return rank;
}
