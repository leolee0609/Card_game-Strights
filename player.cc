#include "player.h"

void Player::setDeck(const std::vector<std::string> &theDeck) {
    for (auto it = theDeck.begin(); it != theDeck.end(); ++it) {
        deck.emplace_back(*it);
    }
}

void Player::printDeck() {
    for (int i = 0; i < 13; ++i) {
        std::cout << deck[i] << " ";
    }
    std::cout << "\n";
    for (int i = 13; i < 26; ++i) {
        std::cout << deck[i] << " ";
    }
    std::cout << "\n";
    for (int i = 26; i < 39; ++i) {
        std::cout << deck[i] << " ";
    }
    std::cout << "\n";
    for (int i = 39; i < 52; ++i) {
        std::cout << deck[i] << " ";
    }
    std::cout << std::endl;
}

Player::Player(bool isHuman, int no) : isHuman{isHuman}, score{0}, baseScore{0}, exePolicy{nullptr}, no{no}, currentPlayed{std::make_pair<char, int>('*', -1)} {}

Player::Player() : currentPlayed{std::make_pair<char, int>(0, -1)}, deck{""}, isHuman{true}, score{-1}, baseScore{-1}, no{-1}, exePolicy{nullptr} {};

Player& Player::operator=(const Player& other) {
    if (this == &other) return *this;
    isHuman = other.isHuman;
    score = other.score;
    baseScore = other.baseScore;
    exePolicy = other.exePolicy;
    no = other.no;
    deck = other.deck;
    currentPlayed = other.currentPlayed;

    return *this;
}

int Player::getNo() const {
    int m = no;
    return m;
}

Player::Player (Player && other) : currentPlayed{other.currentPlayed}, deck{other.deck}, isHuman{other.isHuman}, score{other.score}, baseScore{other.baseScore}, no{other.no}, exePolicy{other.exePolicy} {}

Player::Player (const Player & other) : currentPlayed{other.currentPlayed}, deck{other.deck}, isHuman{other.isHuman}, score{other.score}, baseScore{other.baseScore}, no{other.no}, exePolicy{other.exePolicy} {}

void Player::notify( Subject & whoNotified ) {
    currentPlayed = whoNotified.getInfo();
}

void Player::attachCard(Card newcard) {
    cards.emplace_back(newcard);
}

void Player::returnCard() {
    int len = cards.size();
    for (int i = 0; i < len; ++i) {
        cards.pop_back();
    }

    if (cards.size() != 0) {
        std::cerr << "Warning: cards are not released completely!" << std::endl;
    }
}

void Player::play(Card &playedcard) {
    playedcard.beplayed();
}

void Player::discard(Card &discardedcard) {
    discardedcard.bediscarded();
    std::pair<char, int> information = discardedcard.getInfo();
    int rank = information.second;
    score += rank;
}

void Player::execute() {
    // list of policies
    Human humanPolicy;
    Computer computerPolicy;
    // select a policy
    if (isHuman) {
        exePolicy = &humanPolicy;
    } else {
        exePolicy = &computerPolicy;
    }
    // execute
    if (exePolicy->exeAlg(this) == 0) {
        return;
    } else {
        isHuman = false;
        execute();     // rerun the function
    }
}

void Player::printCards() {
    // print in-hand cards
    std::cout << "Your hand:";
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (it->getStatus() == "in hand") {
            std::cout << " " << it->getRankChar() << it->getSuit();
        }
    }
    std::cout << "\n";
    // print legal plays that are in-hand
    std::cout << "Legal plays:";
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (it->getIslegal()) {
            std::cout << " " << it->getRankChar() << it->getSuit();
        }
    }
    std::cout << std::endl;
}

bool Player::getIshuman() const {
    return isHuman;
}

int Player::getCurscore() const {
    return score;
}

int Player::getScore() const {
    return baseScore;
}

std::pair<char, int> Player::getCurplayed() const {
    return currentPlayed;
}

void Player::combineScore() {
    baseScore += score;
    score = 0;
}

void Player::setCurrentplayed(std::pair<char, int> curp) {
    currentPlayed = curp;
}

void Player::clearDeck() {
    int decklen = deck.size();
    for (int i = 0; i < decklen; ++i) {
        deck.pop_back();
    }
}
