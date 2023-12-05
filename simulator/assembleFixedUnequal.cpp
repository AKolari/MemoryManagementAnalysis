#include "../core/memory_simulator.hpp"

void MemorySimulator::assembleFixedUnEqual(int maxSize) {

    srand(time(0));
    int startingAddress = osSize;
    int remainingMemory = totalMemory - osSize;
    int numberOfPartitions = 0;
    while (remainingMemory > 0) {
        int partitionSize = rand() % maxSize + 1;
        if (partitionSize > remainingMemory) {
            partitionSize = remainingMemory;
        }
        Partition temp(startingAddress, partitionSize);
        partitionList.push_back(temp);
        startingAddress += partitionSize;
        remainingMemory -= partitionSize;
        numberOfPartitions++;
        
    }
    
}
