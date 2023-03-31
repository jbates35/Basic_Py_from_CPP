# Make a normal C++ build environment

cmake_minimum_required(VERSION 3.10)
project(pyCpp1)

# Find the Python interpreter and libraries
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

# Add foo.py to our build
configure_file(foo.py foo.py COPYONLY)

add_executable(pyCpp1 main.cpp)

# Link the Python libraries
target_link_libraries(pyCpp1 ${PYTHON_LIBRARIES})