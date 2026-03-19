#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "MiningTruck.h"
#include "UnloadStation.h"

using std::unique_ptr;
using std::vector;

class Simulation {
    public:
        Simulation(int n, int m);

        void run();

        void advanceTimeStep();

        void placeTruckAtUnloadStation(uint32_t truckId);

    private:
        // Trucks will be moved around between these two lists
        vector<unique_ptr<MiningTruck>> deployedTrucks;
        vector<unique_ptr<UnloadStation>> unloadStations;
    
        uint32_t currentTime;
        uint32_t endTime;
};