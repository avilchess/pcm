cmake_minimum_required(VERSION 3.5.1)
project(pcm_test)
set(CMAKE_CXX_STANDARD 14)

# For MacOS 
IF(APPLE)
set(CMAKE_CXX_FLAGS "-lPcmMsr")
ELSE()
set(CMAKE_CXX_FLAGS "-lpcm -lpthreads")
ENDIF()

add_executable(test main.cpp
        ../cpucounters.cpp
        ../client_bw.cpp
        ../msr.cpp
        ../pci.cpp
        ../mmio.cpp
        ../utils.cpp
        )
target_include_directories(test PUBLIC "../")

