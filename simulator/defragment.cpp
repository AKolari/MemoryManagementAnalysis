#include "../core/memory_simulator.hpp"

void MemorySimulator::defragment(){
    
    for(int i=partitionList.size()-1; i>=0; i-- ){
        if(partitionList[i].isOccupied){
            partitionList.insert(partitionList.begin(), partitionList[i]);
            partitionList.erase(partitionList.begin()+i+1);
            //cout<<"1";
        }
    }
    
    partitionList[0].startingAddress=0;
    for(int i=1; i<partitionList.size(); i++){
        partitionList[i].startingAddress=partitionList[i-1].startingAddress+partitionList[i-1].totalSpace;
        //cout<<"2";
    }
    int newPartitionSize=0;
    while(!partitionList.back().isOccupied){
        newPartitionSize+=partitionList.back().totalSpace;
        partitionList.pop_back();
        //cout<<"3";
    }
    
    Partition temp(partitionList.back().startingAddress+partitionList.back().totalSpace, newPartitionSize);
    partitionList.push_back(temp);
    compactionCount++;
}
