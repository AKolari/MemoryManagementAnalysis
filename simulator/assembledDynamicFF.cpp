#include "../core/memory_simulator.hpp"

void MemorySimulator::assembleDynamicFF(){
    Partition temp(osSize, totalMemory-osSize);
    partitionList.push_back(temp);
}