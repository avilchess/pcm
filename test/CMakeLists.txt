cmake_minimum_required(VERSION 3.11)
project(pcm_test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lpcmMSR")


add_executable(test main.cpp
        ../cpucounters.cpp
        ../client_bw.cpp
        ../msr.cpp
        ../pci.cpp
        ../mmio.cpp
        ../utils.cpp
        )
target_include_directories(scrimp PUBLIC "../")

