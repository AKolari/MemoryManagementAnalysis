#include "../core/memory_simulator.hpp"

//For now, we wil generate 7 partitions, each size 8
void MemorySimulator::assembleFixedEqual() {
    for (int i = osSize; i < totalMemory; i += 8) {
        Partition temp(i, 8);
        partitionList.push_back(temp);
    }

    cout << partitionList.size() << " partitions formed\n";
}