//
//  Vehicle.cpp
//
//  Copyright © 2019 Nicolas BILLOD. All rights reserved.
//

#include "Vehicle.hpp"

#include <vector>

using namespace std;

// ----------------------------------------------------
// Horizontal Vehicles

/*
 (0,0) is top left and its head is on the left
 so going forward is reducing j by 1
 */
bool VehicleH::forward(WorldState &ws){
    if(oldPos.j-1 >= 0 && ws.access(oldPos.i, oldPos.j-1) == "0"){
        head.j=oldPos.j-1;
        act = LEFT;
        return true;
    }
    return false;
}

bool VehicleH::backward(WorldState &ws){
    if(oldPos.j+size <=5 && ws.access(oldPos.i, oldPos.j+size) == "0"){
        head.j=oldPos.j+1;
        act = RIGHT;
        return true;
    }
    return false;
}

// returns all the cells occupied by the vehicle
vector<Pos> VehicleH::getAllPos(){
    vector<Pos> positions;
    for(int i=0; i<size; i++){
        positions.push_back(Pos(head.i, head.j+i));
    }
    return positions;
}


// ----------------------------------------------------
// Vertical vehicles

/*
 (0,0) is top left and its head is on the top
 so going forward is reducing i by 1
 */
bool VehicleV::forward(WorldState &ws){
    if(oldPos.i-1 >= 0 && ws.access(oldPos.i-1, oldPos.j) == "0"){
        head.i=oldPos.i-1;
        act = UP;
        return true;
    }
    return false;
}

bool VehicleV::backward(WorldState &ws){
    if(oldPos.i+size <= 5 && ws.access(oldPos.i+size, oldPos.j) == "0"){
        head.i=oldPos.i+1;
        act = DOWN;
        return true;
    }
    return false;
}

// returns all the cells occupied by the vehicle
vector<Pos> VehicleV::getAllPos(){
    vector<Pos> positions;
    for(int i=0; i<size; i++){
        positions.push_back(Pos(head.i+i, head.j));
    }
    return positions;
}
