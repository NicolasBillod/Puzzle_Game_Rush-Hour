//
//  Move.hpp
//
//  Copyright © 2019 Nicolas BILLOD. All rights reserved.
//

#ifndef Move_hpp
#define Move_hpp

#include <string>


// (0,0) -> top
struct Pos{
    int i;
    int j;
    Pos(int i2, int j2) : i(i2), j(j2)
        { }
};

enum Action {UP, DOWN, RIGHT, LEFT};

struct Move{
    std::string nameVehicle;
    Action action;
    Move(std::string n, Action a) : nameVehicle(n), action(a)
        { }
};

#endif /* Move_hpp */
