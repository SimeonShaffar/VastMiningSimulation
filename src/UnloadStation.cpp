#include "UnloadStation.h"

UnloadStation::UnloadStation() : trucks() {}

bool UnloadStation::isVacant() const {
    return trucks.empty();
}

void UnloadStation::addTruck(unique_ptr<MiningTruck> truck) {
    trucks.push(std::move(truck));
}

unique_ptr<MiningTruck> UnloadStation::unloadTruck() {
    if (isVacant()) {
        return nullptr;
    }
    auto truck = std::move(trucks.front());
    trucks.pop();
    return truck;
}