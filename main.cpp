#include <iostream>

#include <vector>
#include <queue>
#include <map>

#include <fstream>

#include "WorldState.hpp"
#include "Vehicle.hpp"
#include "Move.hpp"

using namespace std;

void fillVehiclesVector(vector<Vehicle*>&, WorldState&);

int main() {
    /*string grid[6][6] = {
     {"c1", "c1", "0", "0", "0", "t1"},
     {"t2", "0", "0", "t3", "0", "t1"},
     {"t2", "g", "g", "t3", "0", "t1"},
     {"t2", "0", "0", "t3", "0", "0"},
     {"c2", "0", "0", "0", "c3", "c3"},
     {"c2", "0", "t4", "t4", "t4", "0"}
     };*/
    
    ifstream file("jam21.txt");
    string grid[6][6];
    int w, h;
    file>>w>>h;
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            file>>grid[i][j];
        }
    }
    
    // Create the list of vehicles
    vector<Vehicle*> vehicles;
    
    // Print the grid
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    
    // We are queuing the world states
    // and generating new world states
    // until we reached and end game state
    queue<WorldState> theQueue;
    WorldState endState(grid);
    theQueue.push(endState);
    
    // map to check if it is the first time we see the state
    map<string, int> statesChecked;

    bool hasReachedEnd = false;
    
    while(!hasReachedEnd && theQueue.size()>0){
        WorldState ws = theQueue.front();
        theQueue.pop();
        
        // Ending condition
        if(ws.access(2, 5) == "g"){
            hasReachedEnd=true;
            endState = ws;
            break;
        }
        
        // Update the vehicles list with positions
        // of this world state
        fillVehiclesVector(vehicles, ws);
        
        for(int i=0; i<vehicles.size(); i++){               // for each vehicle
            if(vehicles[i]->forward(ws)){                   // we check forwards
                WorldState temp(ws, vehicles[i]);
                // only creates a world state if not encountered before
                if(statesChecked.find(temp.getState())==statesChecked.end()){
                    theQueue.push(temp);
                    statesChecked[temp.getState()]++;
                }
            }
            if(vehicles[i]->backward(ws)){                  // we check backwards
                WorldState temp(ws, vehicles[i]);
                // only creates a world state if not encountered before
                if(statesChecked.find(temp.getState())==statesChecked.end()){
                    theQueue.push(temp);
                    statesChecked[temp.getState()]++;
                }
            }
        }
        
        // This state has been checked
        statesChecked[ws.getState()]++;
    }
    
    
    for(int i=0; i<vehicles.size(); i++){
        delete vehicles[i];
    }
    
    
    if(!hasReachedEnd){
        cout<<"No solution"<<endl;
    }
    else{
        cout<<"Found a solution: "<<endl;
        endState.printPath();
        cout<<"\nEnd state: "<<endl;
        endState.printState();
    }
}


/*
 Fills the vehicle vector with different with VehicleH* and VehicleV*
 based on their position in this world state
 */
void fillVehiclesVector(vector<Vehicle*>& vehicles, WorldState& ws){
    for(int i=0; i<vehicles.size(); i++){
        delete vehicles[i];
    }
    vehicles.clear();
    
    string copyGrid[6][6];
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            copyGrid[i][j]=ws.access(i, j);
        }
    }
    
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(copyGrid[i][j] != "0"){ // Vehicle found
                // Horizontal vehicles
                if(j<5 && copyGrid[i][j+1] == copyGrid[i][j]){ // and next is same
                    if(copyGrid[i][j][0]=='c' || copyGrid[i][j][0]=='g'){
                        VehicleH* v = new VehicleH(2, Pos(i,j), copyGrid[i][j]);
                        vehicles.push_back(v);
                    }
                    else{
                        VehicleH* v = new VehicleH(3, Pos(i,j), copyGrid[i][j]);
                        vehicles.push_back(v);
                        copyGrid[i][j+2] = "0";
                    }
                    copyGrid[i][j] = "0";
                    copyGrid[i][j+1] = "0";
                }
                // Vertical vehicles
                else if(i<5 && copyGrid[i+1][j] == copyGrid[i][j]){
                    if(copyGrid[i][j][0]=='c'){
                        VehicleV* v = new VehicleV(2, Pos(i,j), copyGrid[i][j]);
                        vehicles.push_back(v);
                    }
                    else{
                        VehicleV* v = new VehicleV(3, Pos(i,j), copyGrid[i][j]);
                        vehicles.push_back(v);
                        copyGrid[i+2][j] = "0";
                    }
                    copyGrid[i][j] = "0";
                    copyGrid[i+1][j] = "0";
                }
            }
        }
    }
}
