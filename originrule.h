#ifndef ORIGINRULE_H
#define ORIGINRULE_H
#include "gameplay.h"
#include "player.h"


class Originrule : public Gameplay {
    virtual void recalculate() override;
    virtual void printGame(Player * thePlayer) override;
    virtual Player * findfirst() override;
    virtual Player * gotoNext(Player * current) override;
    virtual bool ifEnd() override;    // returns false if there are still cards in hand, otherwise true
    virtual void printScoring() override;

    public:
    virtual bool gameOver() override;
    virtual ~Originrule();
};

#endif
