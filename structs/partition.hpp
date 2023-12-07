#ifndef MEMORYMANAGEMENTANALYSIS_PARTITION_HPP
#define MEMORYMANAGEMENTANALYSIS_PARTITION_HPP

#include "process.hpp"

// class that contains partition data and behavior
class Partition {
public:
    Process currentProcess;
    int startingAddress;
    int totalSpace;
    int occupiedSpace;
    bool isOccupied;

    Partition(int startingAddress, int totalSpace){
        this->startingAddress = startingAddress;
        this->totalSpace = totalSpace;
        occupiedSpace = 0;
        isOccupied = false;

    }

    bool fillPartition(Process newProcess);
    Process emptyPartition();
    bool operator < (const Partition &other);
};

#endif //MEMORYMANAGEMENTANALYSIS_PARTITION_HPP
