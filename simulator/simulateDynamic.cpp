#include "../core/memory_simulator.hpp"

void MemorySimulator::simulateDynamic(vector<Process> processList){
    int end = processList[0].finishTime;

    for(int i=0; i<=end; i++){
        // Check all partitions, and see if there are any complete processes. If so, remove them.
        for (int j = 0; j < partitionList.size(); j++) {
            if (partitionList[j].currentProcess.finishTime == i) {
                partitionList[j].emptyPartition();
            }

            //If two adjacent processes are empty, merge them
            if (j > 0) {
				if (!partitionList[j].isOccupied && !partitionList[j-1].isOccupied) {
					partitionList[j - 1].totalSpace += partitionList[j].totalSpace;
					partitionList.erase(partitionList.begin()+j);
					j--;
				}

            
        }

        if (!processList.empty()) {
            while (processList.back().arrivalTime == i) {
                enteredProcesses++;
                Process temp = processList.back();
                processList.pop_back();

                bool failureFlag = 1; // failure flag is used to check if the process was not placed

                // iterate through the partition list
                for (int j = 0; j < partitionList.size(); j++) {
                    if (partitionList[j].fillPartition(temp)) {
                        failureFlag = 0;

                        int newAddress =partitionList[j].startingAddress+partitionList[j].occupiedSpace;
                        int newSize = partitionList[j].totalSpace - partitionList[j].occupiedSpace;
                        Partition temp(newAddress, newSize);
                        partitionList[j].totalSpace=partitionList[j].occupiedSpace;
                        partitionList.insert(partitionList.begin()+j+1, temp);
                        break;
                    }
                    else {
                        if(!partitionList[j].isOccupied){
                            averageExternalFragmentation+=partitionList[j].totalSpace;
                        }
                    }
                }
                // If we failed to place our process, increment the number of failures by one
                if (failureFlag) {
                    //We need to defragment -- Call defragment()
                    defragment();
                    for (int j = 0; j < partitionList.size(); j++) {
                        if (partitionList[j].fillPartition(temp)) {
                            failureFlag = 0;
                            int newAddress =partitionList[j].startingAddress+partitionList[j].occupiedSpace;
                            int newSize = partitionList[j].totalSpace - partitionList[j].occupiedSpace;
                            Partition temp(newAddress, newSize);
                            partitionList[j].totalSpace=partitionList[j].occupiedSpace;
                            partitionList.insert(partitionList.begin()+j+1, temp);
                            break;
                        }
                    }
                }

                if(failureFlag){
                    failureCount++;
                }

                // Iterate through the partition list, and get the total internal fragmentation currently in memory, and the current memory utilization
                double usedMemory = 0;
                for (int j = 0; j < partitionList.size(); j++) {
                    // if (partitionList[j].isOccupied) {
                    // averageInternalFragmentation += (partitionList[j].totalSpace - //partitionList[j].occupiedSpace);
                    usedMemory += partitionList[j].occupiedSpace;
                }
                averageMemoryUtilization += (usedMemory / totalMemory * 100);

                // Here we check if the vector is empty. The way the while loop is set up, its possible the while loop will call back even after the vector is empty.
                if (processList.empty())
                    break;

            }
        }
    }

    // Complete final calculations
    averageExternalFragmentation = averageExternalFragmentation / enteredProcesses;
    averageMemoryUtilization = averageMemoryUtilization / enteredProcesses;

    // When the simulation is done, output everything
    cout << "\n DYNAMIC FIRST FIT PARTITION:\n";
    cout << "Average External Fragmentation: " << averageExternalFragmentation << " MB\n";
    cout<< "Number of Compactions: "<<compactionCount<<endl;
    cout << "Number of Allocation Fails: " << failureCount << endl;
    cout << "Average Memory Allocation: " << averageMemoryUtilization << "%\n";
}
