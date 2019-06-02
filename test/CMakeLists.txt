cmake_minimum_required(VERSION 3.11)
project(pcm_test)
set(CMAKE_CXX_STANDARD 14)

# For MacOS 
IF(APPLE)
set(CMAKE_CXX_FLAGS "-lPcmMsr")
ENDIF()

IF(UNIX)
set(CMAKE_CXX_FLAGS "lpcm")
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

