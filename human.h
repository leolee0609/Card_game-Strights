#ifndef HUMAN_H
#define HUMAN_H
#include "execution.h"
#include "player.h"
#include <iostream>
#include <sstream>

struct Human : public Execution {
    virtual int exeAlg(Player *p) override;
};


#endif
