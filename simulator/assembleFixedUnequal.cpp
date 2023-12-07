#include "../core/memory_simulator.hpp"

void MemorySimulator::assembleFixedUnEqual() {

    int startingAddress = osSize;
    
    int numberOfPartitions = 11;
    int partitions[11] = {2,2,4,4,4,4,6,6,8,8,8};
    
    for(int i = 0; i < numberOfPartitions;i++)
    {
        Partition temp(startingAddress, partitions[i]);
        partitionList.push_back(temp);
        startingAddress += partitions[i];
     
    }
  
}
