#ifndef BATTLE_H_INCLUDED
#define BATTLE_H_INCLUDED

#include "Ship.h"

namespace battle
{
    enum PlayerType{ human, cpu};

    struct ShipNode;

    typedef ShipNode* ShipPtr;

    struct ShipNode
    {
        Ship component;
        ShipPtr next;
    };


}

#endif // BATTLE_H_INCLUDED
