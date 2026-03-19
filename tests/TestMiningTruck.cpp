#include <gtest/gtest.h>
#include "MiningTruck.h"

TEST(TestMiningTruck, IdIsStoredCorrectly) {
    MiningTruck truck(5);
    EXPECT_EQ(truck.id(), 5u);
}

TEST(TestMiningTruck, NewTruckIsNotReadyToUnload) {
    MiningTruck truck(0);
    EXPECT_FALSE(truck.isReadyToUnload());
}

TEST(TestMiningTruck, TaskFinishedReturnsFalseForTimeZero) {
    MiningTruck truck(0);
    
    EXPECT_FALSE(truck.taskFinished(0));
}

TEST(TestMiningTruck, TaskFinishedReturnsTrueForLargeTime) {
    MiningTruck truck(0);
    EXPECT_TRUE(truck.taskFinished(10000));
}

TEST(TestMiningTruck, TotalUnloadsStartsAtZero) {
    MiningTruck truck(0);
    EXPECT_EQ(truck.totalUnloads(), 0u);
}
