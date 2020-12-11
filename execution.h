#ifndef EXECUTION_H
#define EXECUTION_H

class Player;
struct Execution{
    // returns 0 if successfully finished, returns 1 otherwise
    virtual int exeAlg(Player *p) = 0;     
};

#endif
