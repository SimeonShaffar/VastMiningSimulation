#include "Simulation.h"

Simulation::Simulation(int n, int m) {
    deployedTrucks.reserve(n);
    unloadStations.reserve(m);

    for (int i = 0; i < n; i++) {
        deployedTrucks.push_back(std::make_unique<MiningTruck>(i));
    }
    for (int i = 0; i < m; i++) {
        unloadStations.push_back(std::make_unique<UnloadStation>(i));
    }

    currentTime = 0;
    endTime = 72 * 12; // 72 hours * 12, 5 minute time steps per hour
}

void Simulation::run() {
    while (currentTime < endTime) {
        advanceTimeStep();
    }

    std::cout << "Simulation completed" << std::endl;
}

void Simulation::advanceTimeStep() {
    currentTime++;

    std::cout << "Simulation advancing to time step " << currentTime << std::endl;

    for (auto& truck : deployedTrucks) {
        if (truck->taskFinished(currentTime)) {
            truck->startNextTask(currentTime);

            if (truck->isAtUnloadStation()) {
                std::cout << "\tTruck " << truck->id() << " is at unload station" << std::endl;
                placeTruckAtUnloadStation(std::move(truck));
            }
        }
    }

    // for (auto& station : unloadStations) {
    //     // If the station is vacant, skip it
    //     if (station->isVacant()) continue;
        
    //     // Pop the first truck off the station
    //     unique_ptr<MiningTruck> truck = station->unloadTruck();
    // }
}

void Simulation::placeTruckAtUnloadStation(unique_ptr<MiningTruck> truck) {
    int shortestLine = 0;  // Index of the shortest line
    int shortestLineLength = unloadStations[0]->lineSize();

    std::cout << "Placing truck " << truck->id() << " at unload station " << shortestLine << std::endl;

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

    // Add the truck to the shortest line
    // unloadStations[shortestLine]->addTruck(std::move(truck));
}