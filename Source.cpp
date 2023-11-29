#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
using namespace std;

//struct containing process information
struct Process {
	int processNumber;
	int arrivalTime;
	int sizeOfSpace;
	int finishTime;

	//default constructor
	Process() {
		processNumber=-1;
		arrivalTime=-1;
		sizeOfSpace=-1;
		finishTime=-1;
	}
	//non default constructor
	Process( int processNumber, int arrivalTime, int sizeOfSpace, int finishTime) {
		this->processNumber = processNumber;
		this->arrivalTime = arrivalTime;
		this->sizeOfSpace = sizeOfSpace;
		this->finishTime = finishTime;

	}

};

//class that contains partition data and behavior
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

	//Fill your partition with a process. If we are doing dynamic partitioning, the memory class will alter the total space of this partition and create a new one with a new starting address
	bool fillPartition(Process newProcess) {
		if (newProcess.sizeOfSpace <= totalSpace &&!isOccupied) {
			currentProcess = newProcess;
			occupiedSpace = newProcess.sizeOfSpace;
			isOccupied = true;
			return true;
		}
		return false;
		
	}

	//Remove the process from the partition
	Process emptyPartition() {
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
	bool operator < (const Partition &other) {
		return (startingAddress < other.startingAddress);
	}

};


class MemorySimulator {
public:
	int totalMemory;
	int osSize;
	vector<Partition> partitionList;
	int enteredProcesses;
	double averageInternalFragmentation;
	double averageExternalFragmentation;
	double averageMemoryUtilization;
	int compactionCount;
	int failureCount;


	//For now, make totalMemory=64, and osSize=8
	MemorySimulator(int totalMemory, int osSize) {
		this->totalMemory = totalMemory;
		this->osSize = osSize;
		enteredProcesses = 0;
		averageInternalFragmentation = 0;
		averageExternalFragmentation = 0;
		averageMemoryUtilization = 0;
		compactionCount = 0;
		failureCount = 0;
	}


	//Function to empty the partitions
	void clearPartitions() {
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


	//For now, we wil generate 7 partitions, each size 8
	void assembleFixedEqual() {
		for (int i = osSize; i < totalMemory; i += 8) {
			Partition temp(i, 8);
			partitionList.push_back(temp);
		}

	}



	void assembleFixedUnEqual(int maxSize) {

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
			cout << "NEW PARTITION: SIZE " << partitionSize << endl;;
		}

		cout << endl << numberOfPartitions << endl;
		

	}


	void simulateFixed(vector<Process> processList) {



		int end = processList[0].finishTime;
		//The outermost For loop simulates the passage of time. It keeps going until the final processes exit time has passed
		for (int i = 0; i <= end; i++) {
			//cout << processList[0].finishTime;


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

		//Complete final calculations
		averageInternalFragmentation = averageInternalFragmentation / enteredProcesses;
		averageMemoryUtilization = averageMemoryUtilization / enteredProcesses;


		//When the simulation is done, output everything

		cout << "\n EQUAL FIXED PARTITION:\n";
		cout << "Average Internal Fragmentation: " << averageInternalFragmentation << " MB\n";
		cout << "Number of Allocation Fails: " << failureCount << endl;
		cout << "Average Memory Allocation: " << averageMemoryUtilization << "%\n";















	}










	


















};













int main() {



	ifstream fin;
	
	fin.open("ProcessList.txt");

	int numberOfProcesses;
	fin >> numberOfProcesses;
	vector<Process> processList;
	int index, arrival, size, finish;

	for (int i = 0; i < numberOfProcesses; i++) {
		fin >> index >> arrival >> size >> finish;
		Process temp(index, arrival, size, finish);
		processList.insert(processList.begin(), temp);

	}
	

	MemorySimulator mem(64, 8);
	mem.assembleFixedEqual();

	mem.simulateFixed(processList);
	mem.clearPartitions();
	mem.assembleFixedUnEqual(15);
	
	mem.simulateFixed(processList);
	
	
	






	return 0;
}