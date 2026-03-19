#pragma once

#include <queue>
#include <memory>
#include "MiningTruck.h"

class UnloadStation {
    public:
        UnloadStation(uint32_t id);

        uint32_t id() const { return id_; }

        bool isVacant() const;
        uint32_t lineSize() const;

        void addTruck(std::unique_ptr<MiningTruck> truck);
        std::unique_ptr<MiningTruck> unloadTruck();

    private:
        const uint32_t id_;
        std::queue<std::unique_ptr<MiningTruck>> trucksLine_;
};