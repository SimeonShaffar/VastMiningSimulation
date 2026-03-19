#pragma once

#include <deque>
#include <memory>
#include <iostream>

#include "MiningTruck.h"

// Class object for representing an unload station in the simulation
class UnloadStation {
    public:
        UnloadStation(uint32_t id);

        uint32_t id() const { return id_; }

        bool isVacant() const;
        uint32_t lineSize() const;

        void addTruck(std::unique_ptr<MiningTruck> truck);
        std::unique_ptr<MiningTruck> unloadTruck();         // See unique_ptr explanation in Simulation.h

        uint32_t totalDumps() const { return totalDumps_; }

        
        void timeStepAdvanced();    // Used for tallying up statistics

        uint32_t totalUnloadsFromAllTrucks() const;
        uint32_t totalLineWaitTimeFromAllTrucks() const;
        uint32_t averageLineSize() const;
        void printStatisticsForAllTrucks() const;
        void printStatistics() const;

    private:
        const uint32_t id_;

        // Using a deque because it is modeling a line, which is a textbook FIFO data structure,
        // but we also want to be able to iterate through it, making a queue less useful than a deque
        std::deque<std::unique_ptr<MiningTruck>> trucksLine_;

        uint32_t totalDumps_;              // Total number of dumps into this station  
        uint32_t totalLineSize_;           // Summed up line sizes accross all time steps
};