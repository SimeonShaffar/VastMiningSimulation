#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "MiningTruck.h"
#include "UnloadStation.h"

class Simulation {
    public:
        Simulation(uint32_t n, uint32_t m);

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
        std::vector<std::unique_ptr<MiningTruck>> deployedTrucks;
        std::vector<std::unique_ptr<UnloadStation>> unloadStations;
    
        uint32_t currentTime_;
        uint32_t endTime_;
};