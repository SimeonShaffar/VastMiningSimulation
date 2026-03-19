#include <gtest/gtest.h>
#include "Args.h"

TEST(TestArgs, ParseArgsWithValidInput) {
    char arg0[] = "VastMiningSimulation";
    char arg1[] = "50";
    char arg2[] = "5";
    char* argv[] = {arg0, arg1, arg2};

    Args args = parseArgs(3, argv);

    EXPECT_EQ(args.n, 50u);
    EXPECT_EQ(args.m, 5u);
}

TEST(TestArgs, ParseArgsReturnsDefaultsWhenInsufficientArgs) {
    char arg0[] = "VastMiningSimulation";
    char* argv[] = {arg0};

    Args args = parseArgs(1, argv);

    EXPECT_EQ(args.n, 100u);
    EXPECT_EQ(args.m, 10u);
}

TEST(TestArgs, ParseArgsWithGarbageInput) {
    char arg0[] = "VastMiningSimulation";
    char arg1[] = "not_a_number";
    char arg2[] = "not_a_number";
    char* argv[] = {arg0, arg1, arg2};

    Args args = parseArgs(3, argv);

    EXPECT_EQ(args.n, 0u);
    EXPECT_EQ(args.m, 0u);
}
