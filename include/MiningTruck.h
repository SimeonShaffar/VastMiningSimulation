#pragma once

#include <random>
#include <iostream>

// Class for representing a mining truck in the simulation
class MiningTruck {
    public:
        MiningTruck(uint32_t id);
        
        uint32_t id() const { return id_; }

        bool isReadyToUnload() const { return task_ == Task::AT_UNLOAD_STATION; }

        bool taskFinished(uint32_t currentTime) const;

        void startNextTask(uint32_t currentTime);

        uint32_t totalUnloads() const { return totalUnloads_; }
        uint32_t totalLineWaitTime() const { return totalLineWaitTime_; }
        void printStatistics() const;

    private:
        const uint32_t id_;

        enum class Task {
            AT_MINING_SITE,
            HEADING_TO_UNLOAD,
            AT_UNLOAD_STATION,
            HEADING_TO_SITE,            
        } task_;

        uint32_t endTime_;

        static uint32_t getMiningDuration();

        uint32_t totalUnloads_;         // Total number of successful unloads
        uint32_t totalLineWaitTime_;    // Total time the truck spent in the line
        uint32_t lineEntranceTime_;     // Time the truck most recently entered the line
};