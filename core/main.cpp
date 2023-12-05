#include <iostream>
#include <fstream>
#include "memory_simulator.hpp"
#include <filesystem>
using namespace std;

int main() {
    ifstream fin;
    cout << "Current Working Directory: " << std::filesystem::current_path() << endl;

    // basically problem is that it starts looking for the ProcessList.txt from the working directory. Using absolute filepath for ProcessList.txt fixes the probelm for now.
    //fin.open("/...insert absolute path.../ProcessList.txt");
    fin.open("/...absolutepath.../ProcessList.txt");

    if (fin.is_open()) {
        cout << "File opened";
    } else if (!fin.is_open()) {
        cout << "File not opened";
    }
    cout << "\n";

    int numberOfProcesses;
    fin >> numberOfProcesses;
    vector <Process> processList;
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
