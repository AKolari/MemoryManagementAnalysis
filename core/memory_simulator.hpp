#ifndef MEMORYMANAGEMENTANALYSIS_MEMORY_SIMULATOR_HPP
#define MEMORYMANAGEMENTANALYSIS_MEMORY_SIMULATOR_HPP
#include "../structs/partition.hpp"
#include "../structs/process.hpp"
#include <iostream>
#include <vector>
using namespace std;

class MemorySimulator {
public:
    int totalMemory;
    int osSize;
    vector<Partition> partitionList;
    int enteredProcesses;
    double averageInternalFragmentation;
    double averageExternalFragmentation;
    double averageMemoryUtilization;
    int compactionCount;
    int failureCount;

    //For now, make totalMemory=64, and osSize=8
    MemorySimulator(int totalMemory, int osSize) {
        this->totalMemory = totalMemory;
        this->osSize = osSize;
        enteredProcesses = 0;
        averageInternalFragmentation = 0;
        averageExternalFragmentation = 0;
        averageMemoryUtilization = 0;
        compactionCount = 0;
        failureCount = 0;
    }

    void clearPartitions();
    void assembleFixedEqual();
    void assembleFixedUnEqual(int maxSize);
    void simulateFixed(vector<Process> processList);

    void assembleDynamicFF();
    void simulateDynamic(vector<Process> processList);
    void defragment();
};

#endif //MEMORYMANAGEMENTANALYSIS_MEMORY_SIMULATOR_HPP
