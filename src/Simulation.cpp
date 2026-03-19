#include "Simulation.h"

Simulation::Simulation(uint32_t n, uint32_t m) {
    deployedTrucks.reserve(n);
    unloadStations.reserve(m);

    for (int i = 0; i < n; i++) {
        deployedTrucks.push_back(std::make_unique<MiningTruck>(i));
    }
    for (int i = 0; i < m; i++) {
        unloadStations.push_back(std::make_unique<UnloadStation>(i));
    }

    currentTime_ = 0;
    endTime_ = 72 * 12; // 72 hours * 12, 5 minute time steps per hour
}

void Simulation::run() {
    while (currentTime_ < endTime_) {
        advanceTimeStep();
    }

    std::cout << "Simulation completed" << std::endl;
}

void Simulation::advanceTimeStep() {
    currentTime_++;

    std::cout << "Simulation advancing to time step " << currentTime_ << std::endl;

    // Decrement to ensure that removing a truck does not screw up indexing
    for(int i = deployedTrucks.size() - 1; i >= 0; i--) {
        if (deployedTrucks[i]->taskFinished(currentTime_)) {
            deployedTrucks[i]->startNextTask(currentTime_);

            if (deployedTrucks[i]->isReadyToUnload()) {
                std::cout << "\tTruck " << deployedTrucks[i]->id() << " is at unload station" << std::endl;
                placeTruckAtUnloadStation(i);
            }
        }
    }

    for (auto& station : unloadStations) {
        // If the station is vacant, skip it
        if (station->isVacant()) continue;
        
        // Pop the first truck off the station
        std::unique_ptr<MiningTruck> truck = station->unloadTruck();

        // Add the truck back to the deployed trucks list
        if (truck) {
            truck->startNextTask(currentTime_);
            deployedTrucks.push_back(std::move(truck));
        }
    }
}

void Simulation::placeTruckAtUnloadStation(uint32_t truckIndex) {
    // Pop the truck from the deployed trucks list
    std::unique_ptr<MiningTruck> truck = std::move(deployedTrucks[truckIndex]);
    deployedTrucks.erase(deployedTrucks.begin() + truckIndex);

    int shortestLine = 0;  // Index of the shortest line
    int shortestLineLength = unloadStations[0]->lineSize();

    for(int i = 0; i < unloadStations.size(); i++) {
        // Immediately add the truck to the station if it is vacant
        if (unloadStations[i]->isVacant()) {
            std::cout << "\tPlacing truck " << truck->id() << " at empty unload station " << i << std::endl;
            unloadStations[i]->addTruck(std::move(truck));
            
            return;
        }
        // Otherwise, track the shortest line out of all the stations
        else if (unloadStations[i]->lineSize() < shortestLineLength) {
            shortestLine = i;
            shortestLineLength = unloadStations[i]->lineSize();
        }
    }

    std::cout << "\tPlacing truck " << truck->id() << " at unload station " << shortestLine 
     << " with line size " << shortestLineLength << std::endl;

    unloadStations[shortestLine]->addTruck(std::move(truck));
}