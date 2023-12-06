cmake_minimum_required(VERSION 3.26)
project(MemoryManagementAnalysis)

set(CMAKE_CXX_STANDARD 23)

add_executable(MemoryManagementAnalysis
        core/main.cpp
        structs/partition.cpp
        core/memory_simulator.cpp
        simulator/assembledFixedEqual.cpp
        simulator/assembleFixedUnequal.cpp
        simulator/simulateFixed.cpp
        simulator/assembledDynamicFF.cpp
        simulator/defragment.cpp
        simulator/simulateDynamic.cpp
)
