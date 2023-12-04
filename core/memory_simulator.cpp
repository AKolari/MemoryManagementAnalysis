#include "memory_simulator.hpp"

//Function to empty the partitions
void MemorySimulator::clearPartitions() {
    while (!partitionList.empty()) {
        partitionList.pop_back();
    }

    averageInternalFragmentation = 0;
    averageExternalFragmentation = 0;
    averageMemoryUtilization = 0;
    enteredProcesses = 0;
    compactionCount = 0;
    failureCount = 0;
}