#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "MiningTruck.h"
#include "UnloadStation.h"

class Simulation {
    public:
        Simulation(uint32_t n, uint32_t m);

        void run();

        void advanceTimeStep();

        void placeTruckAtUnloadStation(uint32_t truckIndex);

    private:
        // Trucks will be moved around between these two lists
        std::vector<std::unique_ptr<MiningTruck>> deployedTrucks;
        std::vector<std::unique_ptr<UnloadStation>> unloadStations;
    
        uint32_t currentTime_;
        uint32_t endTime_;
};