#include "UnloadStation.h"

UnloadStation::UnloadStation(uint32_t id) : id_(id), trucks() {}

bool UnloadStation::isVacant() const {
    return trucks.empty();
}

uint32_t UnloadStation::lineSize() const {
    return trucks.size();
}

void UnloadStation::addTruck(unique_ptr<MiningTruck> truck) {
    trucks.push(std::move(truck));
}

unique_ptr<MiningTruck> UnloadStation::unloadTruck() {
    if (isVacant()) { return nullptr; }

    // Move the truck out of the station
    unique_ptr<MiningTruck> truck = std::move(trucks.front());

    // Pop the remaining nullptr out of the queue
    trucks.pop();

    // Return the truck
    return truck;
}