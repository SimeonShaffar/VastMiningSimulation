# Vast Mining Simulation
**Simeon Shaffar 19 March 2026**

This repository demonstrates a simple simulation of a mining operation on the Moon lasting 72 hours.

It comprises the following elements:
- Mining Sites: locations where Helium 3 is located
- Mining Trucks: vehicles which can harvest Helium 3
- Unload Stations: locations where trucks can deposit their payloads

## Building
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Running
The simulation is configured with 2 variable parameters:
1. ***n***: The number of mining trucks in the simulation
2. ***m***: The number of unload stations in the simulation

These parameters are configured using command line arguments. The following example shows a configuration fo 100 trucks sharing 10 stations.
```bash
cd build
./VastMiningSimulation 1000 10
```

To log results, simply use a linux pipe and write to a text file:
```bash
cd VastMiningSimulation
build/VastMiningSimulation 1000 10 > my_results.txt
```

To run unit tests, simply run the test executable
```bash
cd build
./tests
```