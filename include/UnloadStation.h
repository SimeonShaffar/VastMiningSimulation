#pragma once

#include <deque>
#include <memory>
#include <iostream>

#include "MiningTruck.h"

class UnloadStation {
    public:
        UnloadStation(uint32_t id);

        uint32_t id() const { return id_; }

        bool isVacant() const;
        uint32_t lineSize() const;

        void addTruck(std::unique_ptr<MiningTruck> truck);
        std::unique_ptr<MiningTruck> unloadTruck();

        uint32_t totalDumps() const { return totalDumps_; }

        
        void timeStepAdvanced();    // Used for tallying up statistics

        uint32_t totalUnloadsFromAllTrucks() const;
        uint32_t totalLineWaitTimeFromAllTrucks() const;
        uint32_t averageLineSize() const;
        void printStatisticsForAllTrucks() const;
        void printStatistics() const;

    private:
        const uint32_t id_;
        std::deque<std::unique_ptr<MiningTruck>> trucksLine_;

        uint32_t totalDumps_;              // Total number of dumps into this station  
        uint32_t totalLineSize_;           // Summed up line sizes accross all time steps
};