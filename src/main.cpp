#include <iostream>
#include "Simulation.h"
#include "Args.h"

int main(int argc, char* argv[]) {
    Args args = parseArgs(argc, argv);

    std::cout << "VastMiningSimulation\n\n";

    Simulation simulation(args.n, args.m);

    simulation.run();

    simulation.reportSimulationResults();
    
    return 0;
}
