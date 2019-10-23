#CMake entry point
cmake_minimum_required(VERSION 3.5)

## Add headers
include_directories()

set(MSD_RADIX msd.cpp)
set(LSD_RADIX lsd.cpp)

add_compile_options(
    -std=c++17
    -O2
)

# Add executables
add_executable(msd_radix ${MSD_RADIX})
add_executable(lsd_radix ${LSD_RADIX})

