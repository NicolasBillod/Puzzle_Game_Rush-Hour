//
//  Vehicle.hpp
//
//  Copyright © 2019 Nicolas BILLOD. All rights reserved.
//

#ifndef Vehicle_hpp
#define Vehicle_hpp

#include <string>
#include <vector>
#include "WorldState.hpp"
#include "Move.hpp"

class WorldState;


///////////////////////////////////////////////////////
/////////// Vehicle BASE class
///////////////////////////////////////////////////////

/*
 - A vehicle can be of size 2 or 3 atm
 (if not 2, then it assumes 3)
 - It has a string name ("t1", "c2"...)
 - Its head is the position of the front on the vehicle
 - oldPos is its base position
 (head moves backward and/or forward to create new states)
 - act is the Action performed to get its head from oldPos
 to current head position
 */
class Vehicle {
protected:
    int size;
    std::string name;
    Pos head;
    Pos oldPos;
    Action act;
    
public:
    Vehicle(int s, Pos h, std::string n): size(s), head(h), oldPos(h), name(n)
        { }
    virtual ~Vehicle()
        { }
    std::string getName()
        { return name; }
    Action getAct()
        { return act; }
    virtual bool forward(WorldState& ws) = 0;
    virtual bool backward(WorldState& ws) = 0;
    virtual std::vector<Pos> getAllPos() = 0;
};




///////////////////////////////////////////////////////
/////////// DERIVED classes
///////////////////////////////////////////////////////

// Horizontal vehicles
// Their heads are on the left
class VehicleH : public Vehicle {
public:
    VehicleH(int s, Pos h, std::string n): Vehicle(s,h,n)
        { }
    bool forward(WorldState& ws);
    bool backward(WorldState& ws);
    std::vector<Pos> getAllPos();
};


// ----------------------------------------------------

// Vertical vehicles
// Their heads are on the top
class VehicleV : public Vehicle {
public:
    VehicleV(int s, Pos h, std::string n): Vehicle(s,h,n)
        { }
    bool forward(WorldState& ws);
    bool backward(WorldState& ws);
    std::vector<Pos> getAllPos();
};

#endif /* Vehicle_hpp */
