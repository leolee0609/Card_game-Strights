#include "computer.h"


int Computer::exeAlg(Player *p) {
    for (auto it = (p->cards).begin(); it != (p->cards).end(); ++it) {
        if (((*it).getIslegal() == true) && (it->getStatus() == "in hand")) {
            p->play(*it);
            std::cout << "Player " << p->getNo() << " plays " << (*it).getRankChar() << (*it).getSuit() << std::endl;
            return 0;
        }
    }
    // No legal plays
    for (auto it = (p->cards).begin(); it != (p->cards).end(); ++it) {
        if (((*it).getIslegal() == false) && (it->getStatus() == "in hand")) {
            p->discard(*it);
            std::cout << "Player " << p->getNo() << " discards " << (*it).getRankChar() << (*it).getSuit() << std::endl;
            return 0;
        }
    }
    return 0;
}
