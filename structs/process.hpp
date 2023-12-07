#ifndef MEMORYMANAGEMENTANALYSIS_PROCESS_HPP
#define MEMORYMANAGEMENTANALYSIS_PROCESS_HPP

// struct containing process information
struct Process {
    int processNumber;
    int arrivalTime;
    int sizeOfSpace;
    int finishTime;

    // default constructor
    Process() {
        processNumber=-1;
        arrivalTime=-1;
        sizeOfSpace=-1;
        finishTime=-1;
    }
    // non default constructor
    Process( int processNumber, int arrivalTime, int sizeOfSpace, int finishTime) {
        this->processNumber = processNumber;
        this->arrivalTime = arrivalTime;
        this->sizeOfSpace = sizeOfSpace;
        this->finishTime = finishTime;
    }
};

#endif //MEMORYMANAGEMENTANALYSIS_PROCESS_HPP
