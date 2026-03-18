#include <iostream>

int main() {
    std::cout << "VastMiningSimulation\n";

    // Initialize a vector of mining trucks
        // Each truck tracks a position state, which can be simplified down to an enum
        // Also tracks a time step when the current activity ends
        // A simple function can be called when one activity ends to assign a new activity and a new end time
    
    // Initialize a vector of mining sites
        // Each site owns a vector of pointers to trucks, which will correspond to the trucks "located" at that site
        // Every time step of 5 minutes, it pops one truck off and makes the truck move

    // Iterate over 5 minute time steps for 72 hours
        // Iterate through all the sites and 
           // "pop" one truck off, sending it back to the mines
    
    // Iterate through the trucks
        // If they are sitting in line, ignore (bounce)
        // If they are in transit or drilling, check if the timestep has arrived yet
            // If they are done with moving, start drilling
            // If they are done with drilling, start going back
            // If they are heading back, get the vector of sites and find the shortest line, adding themselves to it
    return 0;
}
