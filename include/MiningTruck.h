#pragma once

#include <random>

class MiningTruck {
    public:
        MiningTruck(uint32_t id);

        enum class Task {
            AT_MINING_SITE,
            HEADING_TO_UNLOAD,
            AT_UNLOAD_STATION,
            HEADING_TO_SITE,            
        } state;

        uint32_t id;

        bool taskFinished(uint32_t currentTime) const;

        void startNextTask(uint32_t currentTime);

    private:
        static uint32_t getMiningDuration();

        uint32_t endTime;
};