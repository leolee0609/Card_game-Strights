#include "chrono"
#include "originrule.h"


// returns whether s can be a positive integer. If it is a negative integer string, convert it into positive and return true
bool isPosInt(std::string & s) {
    int length = s.size();
    if (s[0] == '-') {
        s = s.substr(1, length - 1);
        --length;
    }
    for (int i = 0; i < length; ++i) {
        if (! (('0' <= s[i]) && (s[i] <= '9'))) {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    // set seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    if (argc > 1) {
        std::string s{argv[1]};
        if (isPosInt(s)) {
            unsigned newseed;
            std::istringstream iss{s};
            iss >> newseed;
            seed = newseed;
        }
    }
    // get randomness
    std::default_random_engine theDre{seed};
    int inseed = seed;
    std::cout << inseed << std::endl;
    // select a game rule
    Originrule g;

    // set randomness
    g.setRandom(theDre);

    // set what deck are we going to play with
    std::vector<std::string> theDeck{"AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "TC", "JC", "QC", "KC", "AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "TD", "JD", "QD", "KD", "AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "TH", "JH", "QH", "KH", "AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS", "JS", "QS", "KS"};
    


    // invite players
    int playercount = 4;
    for (int i = 1; i <= playercount; ++i) {
        std::cout << "Is Player" << i << " a human (h) or a computer (c)?" << std::endl;
        std::string cmd;
        std::cin >> cmd;
        // is human
        if (cmd == "h") {
            g.addPlayer(new Player(true, i));
        } else if (cmd == "c") {
            g.addPlayer(new Player(false, i));
        } else {
            std::cerr << "Invalid input. Please input either h or c." << std::endl;
            --i;
            continue;
        }
    }

    // give the deck to the gameplay
    g.setDeck(theDeck);

    // run game
    while (!(g.gameOver())) {
        g.reshuffle();     // reshuffle the deck
        g.getCard();         // distribute the cards
        g.proceed();
        g.returnCard();
    }

    


    return 0;
}
