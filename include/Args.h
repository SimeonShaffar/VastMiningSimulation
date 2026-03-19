#pragma once

#include <cstdint>
#include <cstdlib>

struct Args {
    uint32_t n = 100;       // Number of mining trucks
    uint32_t m = 10;        // Number of unload stations
};

inline Args parseArgs(int argc, char* argv[]) {
    Args args = {};         // Initialize with default values
    if (argc >= 3) {
        args.n = static_cast<uint32_t>(std::atoi(argv[1]));
        args.m = static_cast<uint32_t>(std::atoi(argv[2]));

        std::cout << "Using n = " << args.n << " and m = " << args.m << "\n\n";
    } else {
        std::cout << "Usage: " << argv[0] << " <n> <m>\n";
        std::cout << "n: Number of mining trucks (default: " << args.n << ")\n";
        std::cout << "m: Number of unload stations (default: " << args.m << ")\n\n";
    }

    return args;
}
