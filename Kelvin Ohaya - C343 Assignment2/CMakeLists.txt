cmake_minimum_required(VERSION 3.10)
project(Kelvin_Ohaya___C343_Assignment2)

set(CMAKE_CXX_STANDARD 17)

# Path to Sequence from Assignment1
set(SEQUENCE_DIR "${CMAKE_SOURCE_DIR}/../Kelvin Ohaya - C343-Assignment1/src/Sequence")
# Your main executable, directly compiling Sequence.cpp
add_executable(Kelvin_Ohaya___C343_Assignment2
        "EmployeeRecordShortVersion/ExampleFileReader.cpp"

)

# Add include directories for headers
target_include_directories(Kelvin_Ohaya___C343_Assignment2 PRIVATE
        "${CMAKE_SOURCE_DIR}/EmployeeRecordShortVersion"
)
