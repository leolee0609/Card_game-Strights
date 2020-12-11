#include "gameplay.h"

std::string transRank(int r) {
    std::string ret;
    if (r == 1) {
        ret = "A";
    } else if (r == 10) {
        ret = "T";
    } else if (r == 11) {
        ret = "J";
    } else if (r == 12) {
        ret = "Q";
    } else if (r == 13) {
        ret = "K";
    } else {
        ret = std::to_string(r);
    }
    return ret;
}

void Gameplay::setDeck(std::vector<std::string> & theDeck) {
    for (auto d = theDeck.begin(); d != theDeck.end(); ++d) {
        deck.emplace_back(*d);
    }
}

void Gameplay::setRandom(std::default_random_engine theDre) {
    dre = theDre;
}

void Gameplay::addPlayer(Player * newplayer) {
    players.emplace_back(newplayer);
}

void Gameplay::reshuffle() {
    shuffle (deck.begin(), deck.end(), dre);
    for (auto p = players.begin(); p != players.end(); ++p) {
        (*p)->setDeck(deck);
    }
}

void Gameplay::getCard() {
    int decklen = deck.size();
    int playerlen = players.size();
    int each = decklen / playerlen;
    auto itdeck = deck.begin();
    for (auto it = players.begin(); it != players.end(); ++it) {
        (*it)->setDeck(deck);
        while (((*it)->cards.size() < each) && (itdeck != deck.end())) {
            char theSuit = (*itdeck)[1];
            char theRank = (*itdeck)[0];
            (*it)->attachCard(Card(theSuit, theRank));
            ++itdeck;
        }
    }
    // add observers
    for (auto p = players.begin(); p != players.end(); ++p) {
        for (auto pc = (*p)->cards.begin(); pc != (*p)->cards.end(); ++pc) {
            pc->attach(this);
            for (auto it = players.begin(); it != players.end(); ++it) {
                pc->attach(*it);
            }
        }
    }    
}

void Gameplay::proceed() {
    Player * curplayer = findfirst();
    while (!(ifEnd())) {
        recalculate();
        if (curplayer->getIshuman() == true) {
            printGame(curplayer);
        }
        curplayer->execute();
        curplayer = gotoNext(curplayer);
    }
    printScoring();
}

void Gameplay::notify( Subject & whoNotified ) {
    std::pair<char, int> information = whoNotified.getInfo();
    char theSuit = information.first;
    int theRank = information.second;
    // update fields: clubs, diamonds, hearts, and spades
    if (theSuit == 'C') {
        std::string sRank = transRank(theRank);
        std::string newPlayed = sRank + "C";
        clubs.emplace_back(newPlayed);
    } else if (theSuit == 'D') {
        std::string sRank = transRank(theRank);
        std::string newPlayed = sRank + "D";
        diamonds.emplace_back(newPlayed);
    } else if (theSuit == 'H') {
        std::string sRank = transRank(theRank);
        std::string newPlayed = sRank + "H";
        hearts.emplace_back(newPlayed);
    } else if (theSuit == 'S') {
        std::string sRank = transRank(theRank);
        std::string newPlayed = sRank + "S";
        spades.emplace_back(newPlayed);
    }
}

void Gameplay::returnCard() {
    // pop out cards in players and the currentplayed
    for (auto p = players.begin(); p != players.end(); ++p) {
        (*p)->setCurrentplayed(std::make_pair<char, int>('*', -1));
        int cardslen = (*p)->cards.size();
        for (int i = 0; i < cardslen; ++i) {
            (*p)->cards.pop_back();
        }
    }
    // clear the table
    int clublen = clubs.size();
    for (int i = 0; i < clublen; ++i) {
        clubs.pop_back();
    }
    int diamlen = diamonds.size();
    for (int i = 0; i < diamlen; ++i) {
        diamonds.pop_back();
    }
    int heartlen = hearts.size();
    for (int i = 0; i < heartlen; ++i) {
        hearts.pop_back();
    }
    int spadelen = spades.size();
    for (int i = 0; i < spadelen; ++i) {
        spades.pop_back();
    }
    // clear deck for players
    for (auto p = players.begin(); p != players.end(); ++p) {
        (*p)->clearDeck();
    }
}
