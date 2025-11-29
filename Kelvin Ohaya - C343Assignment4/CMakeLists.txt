cmake_minimum_required(VERSION 3.20)
project(KelvinOhaya_C343_Assignment4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all .cpp/.cc/.cxx files under the project so all sources in the Assignment4 folder are built
file(GLOB_RECURSE ALL_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx"
)

# Exclude files generated under the build directory / CMakeFiles (they can contain a main)
list(FILTER ALL_SOURCES EXCLUDE REGEX ".*/build/.*")
list(FILTER ALL_SOURCES EXCLUDE REGEX ".*/CMakeFiles/.*")

add_executable(spellChecker ${ALL_SOURCES})

target_include_directories(spellChecker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(spellChecker PRIVATE -Wall -Wextra -Wpedantic)