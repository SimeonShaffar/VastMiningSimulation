#include "MiningTruck.h"


MiningTruck::MiningTruck(uint32_t id) : 
    id_(id), task_(Task::AT_MINING_SITE), 
    totalUnloads_(0), totalLineWaitTime_(0) {
    endTime_ = getMiningDuration();
}

bool MiningTruck::taskFinished(uint32_t currentTime) const {
    bool result = currentTime >= endTime_;
    return result;
}

void MiningTruck::startNextTask(uint32_t currentTime) {
    switch (task_) {
        case Task::AT_MINING_SITE:
            task_ = Task::HEADING_TO_UNLOAD;
            endTime_ = currentTime + 6; // 6, 5 minute time steps for 30 minute travel time
            return;
        case Task::HEADING_TO_UNLOAD:
            task_ = Task::AT_UNLOAD_STATION;
            endTime_ = currentTime + 1;  // 5 minute unload time
            lineEntranceTime_ = currentTime;
            return;
        case Task::AT_UNLOAD_STATION:
            totalUnloads_++;              // Successful unload, track for simulation report
            task_ = Task::HEADING_TO_SITE;
            endTime_ = currentTime + 6; // 6, 5 minute time steps for 30 minute travel time
            totalLineWaitTime_ += currentTime - lineEntranceTime_;
            return;
        case Task::HEADING_TO_SITE:
            task_ = Task::AT_MINING_SITE;
            endTime_ = currentTime + getMiningDuration();
            return;
    }
}

uint32_t MiningTruck::getMiningDuration() {
    // Random number between 12 and 60 timesteps corresponding to 1-5 hours
    return rand() % 48 + 12;
}