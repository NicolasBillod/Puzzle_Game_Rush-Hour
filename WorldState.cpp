//
//  WorldState.cpp
//
//  Copyright © 2019 Nicolas BILLOD. All rights reserved.
//

#include "WorldState.hpp"

using namespace std;

WorldState::WorldState(string arr[6][6]){
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            grid[i][j] = arr[i][j];
        }
    }
}

/*
 Creates a state of the world based on the old state
 and the movement of one vehicle
 */
WorldState::WorldState(const WorldState& ws, Vehicle* v){
    // copies the grid and erase the vehicle
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            grid[i][j] = new char[3];
            if(ws.grid[i][j] == v->getName()) // Equals to vehicle name
                grid[i][j] = "0";
            else
                grid[i][j] = ws.grid[i][j];
        }
    }
    
    // put new position of the vehicle
    vector<Pos> vehiclePositions = v->getAllPos();
    for(int k=0; k<vehiclePositions.size(); k++){
        int i = vehiclePositions[k].i;
        int j = vehiclePositions[k].j;
        grid[i][j] = v->getName();
    }
    
    // copies path and add this last movement
    path = ws.path;
    path.push_back(Move(v->getName(), v->getAct()));
}


/*
 Gets the state as a string
 Its is used to check if the state has already been visited
 using a map of those strings
 */
string WorldState::getState() const {
    string res="";
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            res += grid[i][j];
        }
    }
    return res;
}



// -------------------------------------------------------------------------
// Prints grid and paths

void WorldState::printState() const{
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<std::endl;
    }
}

void WorldState::printPath() const {
    cout<<path.size()<<" moves\n\n";
    for(int i=0; i<path.size(); i++){
        cout << path[i].nameVehicle << " ";
        switch (path[i].action) {
            case UP:
                std::cout<<"UP ";
                break;
            case DOWN:
                std::cout<<"DOWN ";
                break;
            case RIGHT:
                std::cout<<"RIGHT ";
                break;
            case LEFT:
                std::cout<<"LEFT ";
                break;
                
            default:
                break;
        };
        cout<<std::endl;
    }
}
