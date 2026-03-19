#pragma once

#include <queue>
#include <memory>
#include "MiningTruck.h"

using std::unique_ptr;
using std::queue;

class UnloadStation {
    public:
        UnloadStation(uint32_t id);

        uint32_t id() const { return id_; }

        bool isVacant() const;
        uint32_t lineSize() const;

        void addTruck(unique_ptr<MiningTruck> truck);
        unique_ptr<MiningTruck> unloadTruck();

    private:
        const uint32_t id_;
        queue<unique_ptr<MiningTruck>> trucks;
};