cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

project(libvox)

# collect all executables
set(SOURCES
    src/util/logger.cpp
    src/app.cpp
    src/main.cpp
)
set(HEADERS
    src/app.hpp
)

# add executables
add_executable(libvox ${SOURCES} ${HEADERS})

# add libraries
target_include_directories(libvox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(libvox
    "-framework Foundation"
    "-framework Metal"
    "-framework MetalKit"
)