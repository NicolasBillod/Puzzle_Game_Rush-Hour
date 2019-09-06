//
//  WorldState.hpp
//
//  Copyright © 2019 Nicolas BILLOD. All rights reserved.
//

#ifndef WorldState_hpp
#define WorldState_hpp

#include <iostream>
#include <vector>

#include "Vehicle.hpp"
#include "Move.hpp"

class Vehicle;


/*
 A WorldState object represents a snapshot of the world
 in a certain configuration
 - the grid holds the board with the names of the vehicles
 - path is a vector holding the diffenrent Moves to get to this state
 (fastest path)
 */
class WorldState{
private:
    std::string grid[6][6];
    std::vector<Move> path;
    
public:
    WorldState(const WorldState& ws, Vehicle* v);
    WorldState(std::string arr[6][6]);
    ~WorldState()
        { }
    std::string access(int i, int j) const
        { return grid[i][j]; }
    std::string getState() const;
    void printState() const;
    void printPath() const;
};

#endif /* WorldState_hpp */
