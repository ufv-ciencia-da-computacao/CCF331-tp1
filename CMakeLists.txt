# CMakeLists.txt
project(graphs)

set(CMAKE_BUILD_TYPE Debug)
set(SOURCE_FILES json.hpp main.cpp)
add_executable(main ${SOURCE_FILES})