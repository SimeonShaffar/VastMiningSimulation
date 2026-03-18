#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <algorithm>

using std::unique_ptr;
using std::vector;

class Simulation {
    public:
        Simulation(int n, int m);

        void advanceTimeStep();

        unique_ptr<UnloadStation> findShortestLine();

    private:
        // Trucks will be moved around between these two lists
        vector<unique_ptr<MiningTruck>> deployedTrucks;
        vector<unique_ptr<UnloadStation>> unloadStations;

        uint32_t currentTime;
        uint32_t endTime;
};