cmake_minimum_required(VERSION 2.6)

project(SourceTesting)


include(CodeCoverage.cmake)

append_coverage_compiler_flags()

# Locate GTest
find_package(GTest REQUIRED)
find_package(Threads REQUIRED) 
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(3rdparty)

set(CMAKE_CXX_STANDARD 17) 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Testing_SOURCE_DIR}/bin)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)


setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_coverage 
EXECUTABLE runTests BASE_DIRECTORY "${PROJECT_SOURCE_DIR}")



# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp)

#target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)


target_link_libraries(runTests Threads::Threads ${GTEST_LIBRARIES} pthread)















