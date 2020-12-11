#ifndef COMPUTER_H
#define COMPUTER_H
#include "execution.h"
#include "player.h"

struct Computer : public Execution {
    virtual int exeAlg(Player *p) override;
};

#endif
