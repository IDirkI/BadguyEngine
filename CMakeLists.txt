cmake_minimum_required(VERSION 3.22.1)

project(badguy_engine) 

# Auto Set SRC files
set(SOURCE_FILES
    "src/main.cpp"
)

# Find Packages
find_package(SDL2 REQUIRED)
find_package(Eigen3 3.4 REQUIRED)

# Include Directories
include_directories("./include/")
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${EIGEN_INCLUDE_DIR})

# Make Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Target Libs
target_link_libraries(
    ${PROJECT_NAME} 
    
    ${SDL2_LIBRARIES} 
    ${EIGEN_LIBRARIES})