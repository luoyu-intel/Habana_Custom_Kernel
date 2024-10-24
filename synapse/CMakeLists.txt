project(synapse)

set(SYNAPSE_INCLUDE_DIR "/usr/include/habanalabs" CACHE STRING "Path to SYNAPSE includes")
set(SYNAPSE_LIB_DIR "/usr/lib/habanalabs" CACHE STRING "Path to SYNAPSE libs")

include_directories(${SYNAPSE_INCLUDE_DIR})
link_directories(${SYNAPSE_LIB_DIR})
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} Synapse)