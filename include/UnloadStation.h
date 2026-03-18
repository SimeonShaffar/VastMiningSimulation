#pragma once

#include <queue>
#include <memory>
#include "MiningTruck.h"

using std::unique_ptr;
using std::queue;

class UnloadStation {
    public:
        UnloadStation();

        bool isVacant() const;

        void addTruck(unique_ptr<MiningTruck> truck);
        unique_ptr<MiningTruck> unloadTruck();

    private:
        queue<unique_ptr<MiningTruck>> trucks;
};