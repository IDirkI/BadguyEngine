cmake_minimum_required(VERSION 3.0.0)
project(badguy_engine)

set(SOURCE_FILES 
    "src/main.cpp"
    )

find_package(SDL2 REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})