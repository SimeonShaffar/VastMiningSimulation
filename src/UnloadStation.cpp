#include "UnloadStation.h"

UnloadStation::UnloadStation(uint32_t id) : id_(id), trucksLine_() {}

bool UnloadStation::isVacant() const {
    return trucksLine_.empty();
}

uint32_t UnloadStation::lineSize() const {
    return trucksLine_.size();
}

void UnloadStation::addTruck(std::unique_ptr<MiningTruck> truck) {
    trucksLine_.push(std::move(truck));
}

std::unique_ptr<MiningTruck> UnloadStation::unloadTruck() {
    if (isVacant()) { return nullptr; }

    // Move the truck out of the station
    std::unique_ptr<MiningTruck> truck = std::move(trucksLine_.front());
    trucksLine_.pop();

    // Return the truck
    return truck;
}