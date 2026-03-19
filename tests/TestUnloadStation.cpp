#include <gtest/gtest.h>
#include "UnloadStation.h"
#include "MiningTruck.h"

TEST(TestUnloadStation, IdIsStoredCorrectly) {
    UnloadStation station(7);
    EXPECT_EQ(station.id(), 7u);
}

TEST(TestUnloadStation, NewStationIsVacant) {
    UnloadStation station(0);
    EXPECT_TRUE(station.isVacant());
    EXPECT_EQ(station.lineSize(), 0u);
}

TEST(TestUnloadStation, LineSizeIncreasesWhenAddingTrucks) {
    UnloadStation station(0);
    auto truck1 = std::make_unique<MiningTruck>(0);
    auto truck2 = std::make_unique<MiningTruck>(1);

    EXPECT_TRUE(station.isVacant());
    station.addTruck(std::move(truck1));
    EXPECT_FALSE(station.isVacant());
    EXPECT_EQ(station.lineSize(), 1u);

    station.addTruck(std::move(truck2));
    EXPECT_EQ(station.lineSize(), 2u);
}

TEST(TestUnloadStation, UnloadTruckReturnsTruckAndShrinksLine) {
    UnloadStation station(0);
    auto truck = std::make_unique<MiningTruck>(0);
    station.addTruck(std::move(truck));

    std::unique_ptr<MiningTruck> unloaded = station.unloadTruck();

    ASSERT_NE(unloaded, nullptr);
    EXPECT_EQ(unloaded->id(), 0u);
    EXPECT_TRUE(station.isVacant());
    EXPECT_EQ(station.totalDumps(), 1u);
}

TEST(TestUnloadStation, UnloadTruckFromVacantReturnsNullptr) {
    UnloadStation station(0);

    std::unique_ptr<MiningTruck> unloaded = station.unloadTruck();

    EXPECT_EQ(unloaded, nullptr);
}