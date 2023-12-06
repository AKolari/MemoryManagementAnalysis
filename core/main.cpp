#include <iostream>
#include <fstream>
#include "memory_simulator.hpp"
#include <filesystem>
using namespace std;

int main() {
    ifstream fin;
    filesystem::path filePath = filesystem::current_path(); // build directory
    filePath = filePath.parent_path(); // project directory
    filePath /= "core/ProcessList.txt"; // txt file

    fin.open(filePath);

    if (!fin.is_open()) {
        cout << "File not opened";
        return 0;
    }

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
    mem.clearPartitions();
    return 0;
}