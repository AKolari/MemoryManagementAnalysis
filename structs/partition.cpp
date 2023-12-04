#include "partition.hpp"

//Fill your partition with a process. If we are doing dynamic partitioning, the memory class will alter the total space of this partition and create a new one with a new starting address
bool Partition::fillPartition(Process newProcess) {
    if (newProcess.sizeOfSpace <= totalSpace &&!isOccupied) {
        currentProcess = newProcess;
        occupiedSpace = newProcess.sizeOfSpace;
        isOccupied = true;
        return true;
    }
    return false;
}

//Remove the process from the partition
Process Partition::emptyPartition() {
    if (!isOccupied) {
        return *(new Process());
    }
    else {
        occupiedSpace = 0;
        isOccupied = false;
        return currentProcess;
    }
}

//overload operator. we use this to compare two partitions, and see which one has an earlier starting address. We will need to do this for dynamic partitions, as they need to be in the correct spot.
bool Partition::operator<(const Partition &other) {
    return (startingAddress < other.startingAddress);
}
