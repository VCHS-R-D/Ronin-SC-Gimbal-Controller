cmake_minimum_required(VERSION 3.9)
project(my-sbus-project)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# This is what you cloned previously.
# After this line a libsbus target is available for linking
add_subdirectory(raspberry-sbus)

# Create a new executable target with a single source file main.cpp
# and link it with the library
add_executable(main main.cpp)
target_link_libraries(main PUBLIC libsbus)