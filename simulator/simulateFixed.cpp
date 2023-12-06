#include "../core/memory_simulator.hpp"

void MemorySimulator::simulateFixed(vector<Process> processList) {
    int end = processList[0].finishTime;
    //The outermost For loop simulates the passage of time. It keeps going until the final processes exit time has passed
    for (int i = 0; i <= end; i++) {

        //Check all partitions, and see if there are any complete processes. If so, remove them.
        for (int j = 0; j < partitionList.size(); j++) {
            if (partitionList[j].currentProcess.finishTime == i) {
                partitionList[j].emptyPartition();
            }
        }

        //Check the list of processes, and if there are processes in the list which need to be placed in memory, start placing
        if (!processList.empty()) {
            while (processList.back().arrivalTime == i) {
                enteredProcesses++;
                Process temp = processList.back();
                processList.pop_back();

                bool failureFlag = 1;//failure flag is used to check if the process was not placed

                //iterate through the partition list
                for (int j = 0; j < partitionList.size(); j++) {
                    //If we successfully placed our processs in a partition, set failre flag to zero, and break out of loop
                    if (partitionList[j].fillPartition(temp)) {
                        failureFlag = 0;
                        break;
                    }
                }

                //If we failed to place our process, increment the number of failures by one
                if (failureFlag) {
                    //cout << temp.processNumber << "\t";
                    failureCount++;
                }

                //Iterate through the partition list, and get the total internal fragmentation currently in memory, and the current memory utilization
                double usedMemory = 0;
                for (int j = 0; j < partitionList.size(); j++) {
                    if (partitionList[j].isOccupied) {
                        averageInternalFragmentation += (partitionList[j].totalSpace - partitionList[j].occupiedSpace);
                    }
                    usedMemory += partitionList[j].occupiedSpace;
                }
                averageMemoryUtilization += (usedMemory / totalMemory * 100);

                //Here we check if the vector is empty. The way the while loop is set up, its possible the while loop will call back even after the vector is empty.
                if (processList.empty())
                    break;
            }
        }
    }

    // Complete final calculations
    averageInternalFragmentation = averageInternalFragmentation / enteredProcesses;
    averageMemoryUtilization = averageMemoryUtilization / enteredProcesses;

    // When the simulation is done, output everything

    cout << "Average Internal Fragmentation: " << averageInternalFragmentation << " MB\n";
    cout << "Number of Allocation Fails: " << failureCount << endl;
    cout << "Average Memory Allocation: " << averageMemoryUtilization << "%\n";
}
