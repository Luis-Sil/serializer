cmake_minimum_required(VERSION 3.10)

project(serializer 
        LANGUAGES CXX)

set(CXX_STANDARD 17)

add_subdirectory(src)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE pugixml)

message("${CMAKE_SOURCE_DIR}")