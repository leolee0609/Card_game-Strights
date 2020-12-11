#include "human.h"


// returns an integer that converts a char-type rank into an integer-type rank
int rankTrans(char charRank) {
    int ret;
    if (charRank == 'A') {
        ret = 1;
    } else if (charRank == 'J') {
        ret = 11;
    } else if (charRank == 'Q') {
        ret = 12;
    } else if (charRank == 'K') {
        ret = 13;
    } else if (charRank == 'T') {
        ret = 10;
    } else {
        ret = charRank - 48;
    }
    return ret;
}

int Human::exeAlg(Player *p) {
    bool refuseddisorplay = false;
    while (true) {
        std::string cmd;
        std::cin >> cmd;
        std::string suits{"CDHS"};
        std::string dig{"A23456789TJQK"};
        if (cmd == "quit") {
            exit(0);
        } else if (cmd == "discard") {
            // check if there are still legal plays
            bool docontinue = false;
            for (auto it = (p->cards).begin(); it != (p->cards).end(); ++it) {
                if ((*it).getIslegal()) {
                    std::cerr << "You have a legal play. You may not discard." << std::endl;
                    refuseddisorplay = true;
                    docontinue = true;
                    break;
                }
            }
            if (docontinue) {
                docontinue = false;
                continue;
            }
            std::string c;
            std::cin >> c;
            // check if the syntax is valid
            if (!((c.size() == 2) && (suits.find(c[1]) != std::string::npos) && (dig.find(c[0]) != std::string::npos))) {
                std::cerr << "Invalid card syntax." << std::endl;
                continue;
            } else {
                char theSuit = c[1];
                char charrank = c[0];
                int theRank = rankTrans(charrank);
                // check if the rank exists
                if (!((1 <= theRank) && (theRank <= 13))) {
                    std::cerr << "Invalid card rank." << std::endl;
                    continue;
                } else {
                    // check if there are still legal plays
                    bool docontinue = false;
                    for (auto it = (p->cards).begin(); it != (p->cards).end(); ++it) {
                        if ((*it).getIslegal()) {
                            std::cerr << "You have a legal play. You may not discard." << std::endl;
                            refuseddisorplay = true;
                            docontinue = true;
                            break;
                        }
                    }
                    if (docontinue) {
                        docontinue = false;
                        continue;
                    }
                    // try to discard it if it exists
                    for (auto it = (p->cards).begin(); it != (p->cards).end(); ++it) {
                        if (((*it).getSuit() == theSuit) && ((*it).getRank() == theRank) && (it->getStatus() == "in hand")) {
                            p->discard(*it);
                            std::cout << "Player " << p->getNo() << " discards " << c << "." << std::endl;
                            return 0;
                        }
                    }
                    std::cerr << "You do not have the card." << std::endl;
                    continue;
                }
            }
        } else if (cmd == "play") {
            std::string playcard;
            std::cin >> playcard;
            if (!((playcard.size() == 2) && (suits.find(playcard[1]) != std::string::npos) && (dig.find(playcard[0]) != std::string::npos))) {
                std::cerr << "Invalid card syntax." << std::endl;
                continue;
            } else {
                char theSuit = playcard[1];
                char charrank = playcard[0];
                int theRank = rankTrans(charrank);
                // check if the rank exists
                if (!((1 <= theRank) && (theRank <= 13))) {
                    std::cerr << "Invalid card rank." << std::endl;
                    continue;
                } else {
                    // check if the card exists
                    bool shouldcontinue = false;
                    for (auto it = (p->cards).begin(); it != (p->cards).end(); ++it) {
                        if (((*it).getSuit() == theSuit) && ((*it).getRank() == theRank) && (it->getStatus() == "in hand")) {
                            if ((*it).getIslegal() == false) {
                                std::cerr << "This is not a legal play." << std::endl;
                                shouldcontinue = true;
                                break;
                            } else {
                                p->play(*it);
                                std::cout << "Player " << p->getNo() << " plays " << playcard << std::endl;
                                return 0;
                            }
                        }
                    }
                    if (shouldcontinue) {
                        shouldcontinue = false;
                        continue;
                    }
                    std::cerr << "You do not have the card." << std::endl;
                    continue;
                }
            }
        } else if (cmd == "deck") {
            p->printDeck();
        } else if (cmd == "ragequit") {
            std::cerr << "Player " << p->getNo() << " ragequits. A computer will now take over." << std::endl;
            return 1;
        } else {
            if (refuseddisorplay) {
                refuseddisorplay = false;
                continue;
            }
            std::cerr << "Invalid command." << std::endl;
            continue;
        }
    }
}

