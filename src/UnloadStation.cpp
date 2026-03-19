#include "UnloadStation.h"

UnloadStation::UnloadStation(uint32_t id) : id_(id), trucksLine_(), totalDumps_(0), totalLineSize_(0) {}

bool UnloadStation::isVacant() const {
    return trucksLine_.empty();
}

uint32_t UnloadStation::lineSize() const {
    return trucksLine_.size();
}

void UnloadStation::addTruck(std::unique_ptr<MiningTruck> truck) {
    trucksLine_.push_back(std::move(truck));
}

std::unique_ptr<MiningTruck> UnloadStation::unloadTruck() {
    if (isVacant()) { return nullptr; }

    // Move the truck out of the station
    std::unique_ptr<MiningTruck> truck = std::move(trucksLine_.front());
    trucksLine_.pop_front();

    totalDumps_++;      // Successful unload, track for end of simulation report

    // Return the truck
    return truck;
}

void UnloadStation::timeStepAdvanced() {
    totalLineSize_ += trucksLine_.size();
}

// Used at the final simiulation report whilst tallying up total dumps from all trucks
uint32_t UnloadStation::totalUnloadsFromAllTrucks() const {
    uint32_t totalUnloads = 0;
    for (const auto& truck : trucksLine_) {
        totalUnloads += truck->totalUnloads();
    }
    return totalUnloads;
}

uint32_t UnloadStation::totalLineWaitTimeFromAllTrucks() const {
    uint32_t totalLineWaitTime = 0;
    for (const auto& truck : trucksLine_) {
        totalLineWaitTime += truck->totalLineWaitTime();
    }
    return totalLineWaitTime;
}

void UnloadStation::printStatisticsForAllTrucks() const {
    for (const auto& truck : trucksLine_) {
        truck->printStatistics();
    }
}

uint32_t UnloadStation::averageLineSize() const {
    return totalLineSize_ / (72 * 12);
}
void UnloadStation::printStatistics() const {
    std::cout << "Unload station " << id_ << " average line size: " << averageLineSize() << "\n";
}