#include "MiningTruck.h"


MiningTruck::MiningTruck(uint32_t id) : id_(id), state(Task::AT_MINING_SITE) {
    endTime = getMiningDuration();
}

bool MiningTruck::taskFinished(uint32_t currentTime) const {
    return currentTime >= endTime;
}

void MiningTruck::startNextTask(uint32_t currentTime) {
    switch (state) {
        case Task::AT_MINING_SITE:
            state = Task::HEADING_TO_UNLOAD;
            endTime = currentTime + 6; // 6, 5 minute time steps for 30 minute travel time
            return;
        case Task::HEADING_TO_UNLOAD:
            state = Task::AT_UNLOAD_STATION;
            endTime = currentTime + 1;  // 5 minute unload time
            return;
        case Task::AT_UNLOAD_STATION:
            state = Task::HEADING_TO_SITE;
            endTime = currentTime + 6; // 6, 5 minute time steps for 30 minute travel time
            return;
        case Task::HEADING_TO_SITE:
            state = Task::AT_MINING_SITE;
            endTime = currentTime + getMiningDuration();
            return;
    }
}

uint32_t MiningTruck::getMiningDuration() {
    // Random number between 12 and 60 timesteps corresponding to 1-5 hours
    return rand() % 48 + 12;
}