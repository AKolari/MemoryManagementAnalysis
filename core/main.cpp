#include <iostream>
#include <fstream>
#include "memory_simulator.hpp"

using namespace std;

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
    
    cout << "\n EQUAL FIXED PARTITION:\n";
    mem.simulateFixed(processList);
    mem.clearPartitions();
    mem.assembleFixedUnEqual(15);
    
    cout << "\n UNEQUAL FIXED PARTITION:\n";
    mem.simulateFixed(processList);
    mem.clearPartitions();
    mem.assembleDynamicFF();
    mem.simulateDynamic(processList);
    
    






    return 0;
}
