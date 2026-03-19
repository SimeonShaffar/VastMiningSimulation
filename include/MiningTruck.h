#pragma once

#include <random>

class MiningTruck {
    public:
        MiningTruck(uint32_t id);

        uint32_t id() const { return id_; }

        bool isAtUnloadStation() const { return state == Task::AT_UNLOAD_STATION; }

        bool taskFinished(uint32_t currentTime) const;

        void startNextTask(uint32_t currentTime);        

    private:
        const uint32_t id_;

        static uint32_t getMiningDuration();

        enum class Task {
            AT_MINING_SITE,
            HEADING_TO_UNLOAD,
            AT_UNLOAD_STATION,
            HEADING_TO_SITE,            
        } state;

        uint32_t endTime;
};