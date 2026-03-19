#include "Simulation.h"

Simulation::Simulation(uint32_t n, uint32_t m) : n_(n), m_(m) {
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

    // Seed the random number generator to get non-deterministic results
    srand(time(nullptr));
}

void Simulation::run() {
    while (currentTime_ < endTime_) {
        advanceTimeStep();
    }
}

void Simulation::advanceTimeStep() {
    currentTime_++;

    // Process trucks at the unload stations first so that no truck
    // ever enters and exits the line at the same time.
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

    // Decrement to ensure that removing a truck does not screw up indexing
    for(int i = deployedTrucks.size() - 1; i >= 0; i--) {
        if (deployedTrucks[i]->taskFinished(currentTime_)) {
            deployedTrucks[i]->startNextTask(currentTime_);

            if (deployedTrucks[i]->isReadyToUnload()) {
                placeTruckAtUnloadStation(i);
            }
        }
    }
}

void Simulation::placeTruckAtUnloadStation(uint32_t truckIndex) {
    // Pop the truck from the deployed trucks list
    std::unique_ptr<MiningTruck> truck = std::move(deployedTrucks[truckIndex]);
    deployedTrucks.erase(deployedTrucks.begin() + truckIndex);

    int shortestLine = 0;  // Index of the shortest line
    int shortestLineLength = unloadStations[0]->lineSize();

    // Iterate over each station, checking for the shortest line
    for(int i = 0; i < unloadStations.size(); i++) {
        // Immediately add the truck to the station if it is vacant
        if (unloadStations[i]->isVacant()) {
            unloadStations[i]->addTruck(std::move(truck));
            return;
        }
        // Otherwise, track the shortest line out of all the stations
        else if (unloadStations[i]->lineSize() < shortestLineLength) {
            shortestLine = i;
            shortestLineLength = unloadStations[i]->lineSize();
        }
    }

    unloadStations[shortestLine]->addTruck(std::move(truck));
}

void Simulation::reportSimulationResults() const {
    // Initialize total parameters
    uint32_t totalDumps = 0;
    uint32_t totalLineWaitTime = 0;
    
    // Tally up total parameters from all stations and trucks
    for (const auto& truck : deployedTrucks) {
        totalLineWaitTime += truck->totalLineWaitTime();
    }
    for (const auto& station : unloadStations) {
        totalDumps += station->totalDumps();
        totalLineWaitTime += station->totalLineWaitTimeFromAllTrucks();
    }

    totalLineWaitTime *= 5; // Convert to minutes

    // Calculate average parameters
    uint32_t averageDumpsPerStation = totalDumps / m_;
    uint32_t averageDumpsPerTruck = totalDumps / n_;
    uint32_t averageLineWaitTimePerTruck = totalLineWaitTime / n_;
    uint32_t averageLineWaitTimePerDump = totalLineWaitTime / totalDumps;

    // Print results
    std::cout << "Simulation completed\n";
    std::cout << "Total number of dumps from all stations: " << totalDumps << "\n";
    std::cout << "Average number of dumps per truck: " << averageDumpsPerTruck << "\n";
    std::cout << "Average number of dumps per station: " << averageDumpsPerStation << "\n";
    std::cout << "Average line wait time per truck: " << averageLineWaitTimePerTruck << " minutes\n";
    std::cout << "Average line wait time per dump: " << averageLineWaitTimePerDump << " minutes\n";
}