#include "originrule.h"


Originrule::~Originrule() {
    int length = players.size();
    for (int i = 0; i < length; ++i) {
        delete players[i];
    }
}

void Originrule::recalculate() {
    for (auto it = players.begin(); it != players.end(); ++it) {
        for (auto itcard = ((*it)->cards).begin(); itcard != ((*it)->cards).end(); ++itcard) {
            // recalculate if it is legal
            int theRank = itcard->getRank();
            std::string theSta{itcard->getStatus()};
            std::pair<char, int> curinfo = (*it)->getCurplayed();
            char curSuit = curinfo.first;
            int currank = curinfo.second;
            char theSuit = itcard->getSuit();
            if ((theSta == "in hand") && ((theRank == 7) || ((theSuit == curSuit) && ((theRank - currank == -1) || (theRank - currank == 1))))) {
                itcard->setIslegal(true);
            }
        }
    }
}

void Originrule::printGame(Player * thePlayer) {
    std::cout << "Cards on the table:\n";

    std::cout << "Clubs:";
    for (auto it = clubs.begin(); it != clubs.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";

    std::cout << "Diamonds:";
    for (auto it = diamonds.begin(); it != diamonds.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";

    std::cout << "Hearts:";
    for (auto it = hearts.begin(); it != hearts.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";

    std::cout << "Spades:";
    for (auto it = spades.begin(); it != spades.end(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";

    thePlayer->printCards();
}

Player * Originrule::findfirst() {
    for (auto it = players.begin(); it != players.end(); ++it) {
        for (auto itcard = ((*it)->cards).begin(); itcard != ((*it)->cards).end(); ++itcard) {
            std::pair<char, int> theinfo = itcard->getInfo();
            char theSuit = theinfo.first;
            int theRank = theinfo.second;

            if ((theRank == 7) && (theSuit == 'S')) {
                std::cout << "A new round begins. It's Player" << (*it)->getNo() << "'s turn to play." << std::endl;
                return *it;
            }
        }
    }
    std::cerr << "Warning: Find no 7S, will start by playre1" << std::endl;
    return *(players.begin());
}

Player * Originrule::gotoNext(Player * current) {
    auto it = players.begin();
    // let it point to current
    while (*it != current) {
        ++it;
    }
    // now it points to current
    ++it;
    if (it != players.end()) {
        return *it;
    } else {
        return *(players.begin());
    }
}

bool Originrule::ifEnd() {
    for (auto it = players.begin(); it != players.end(); ++it) {
        for (auto itcard = ((*it)->cards).begin(); itcard != ((*it)->cards).end(); ++itcard) {
            if (itcard->getStatus() == "in hand") {
                return false;
            }
        }
    }
    return true; 
}

bool Originrule::gameOver() {
    bool isover = false;
    for (auto p = players.begin(); p != players.end(); ++p) {
        if ((*p)->getScore() >= 80) {
            isover = true;
        }
    }
    if (isover) {
        int lowest = (*(players.begin()))->getScore();
        for (auto it = players.begin(); it != players.end(); ++it) {
            if ((*it)->getScore() < lowest) {
                lowest = (*it)->getScore();
            }
        }
        for (auto it = players.begin(); it != players.end(); ++it) {
            if ((*it)->getScore() == lowest) {
                winPlayers.emplace_back((*it)->getNo());
            }
        }
    }

    if (winPlayers.size() == 0) {
        return false;
    } else {
        for (auto no = winPlayers.begin(); no != winPlayers.end(); ++no) {
            std::cout << "Player" << *no << " wins!" << std::endl;
        }
        return true;
    }
}

void Originrule::printScoring() {
    for (auto p = players.begin(); p != players.end(); ++p) {
        // print discards
        std::cout << "Player" << (*p)->getNo() << "'s discards:";
        for (auto itcard = ((*p)->cards).begin(); itcard != ((*p)->cards).end(); ++itcard) {
            if (itcard->getStatus() == "discarded") {
                std::cout << " " << itcard->getRankChar() << itcard->getSuit();
            }
        }
        std::cout << "\n";

        // print scores
        int baseScore = (*p)->getScore();
        int curScore = (*p)->getCurscore();
        int overallScore = baseScore + curScore;
        std::cout << "Player" << (*p)->getNo() << "'s score: " << baseScore << " + " << curScore << " = " << overallScore << "\n";
        (*p)->combineScore();
    }
}
