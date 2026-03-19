#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "MiningTruck.h"
#include "UnloadStation.h"

// Class object for controlling & running the simulation
class Simulation {
    public:
        Simulation(uint32_t n, uint32_t m);

        // uint32_t is used widely here because I want to guarantee unsigned integers 
        // for the vast majority of the project. I also like being more explicit with length
        // because it helps keep in mind what the max value is for the variable.
        uint32_t n() const { return n_; }
        uint32_t m() const { return m_; }

        void run();

        void advanceTimeStep();

        void placeTruckAtUnloadStation(uint32_t truckIndex);

        void reportSimulationResults() const;

    private:
        uint32_t n_;
        uint32_t m_;
        
        // Trucks will be moved around between these two lists
        // Choosing to use unique pointers because it makes it more guaranteed
        // that you will not accidentally create copies of the objects or destroy them
        // 
        // They are also nice for memory management because they let you allocate memory once, and 
        // everything after that is just passing pointers around in the stack.
        //
        // Memory cleanup is also reliable using unique pointers
        std::vector<std::unique_ptr<MiningTruck>> deployedTrucks;
        std::vector<std::unique_ptr<UnloadStation>> unloadStations;
    
        uint32_t currentTime_;
        uint32_t endTime_;
};