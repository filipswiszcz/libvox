cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

project(libvox VERSION 0.0.1) # libvx new name?

# find moltenvk library
if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    find_package(Vulkan)
    message(STATUS "Found MoltenVK with default finder.")
    find_package(GLWF)
    find_package(glm)
endif()

if (WIN32)
    message("win32") # TODO add finder
elseif (LINUX)
    message("linux") # TODO add finder
elseif (APPLE)
    if (NOT VULKAN_FOUND)
        set(CMAKE_FIND_FRAMEWORK NEVER)

        find_library(VULKAN_LIBRARY NAMES MoltenVK HINTS "$ENV{VULKAN_SDK}/lib" "$ENV{VULKAN_SDK}/dylib/macOS" REQUIRED)
        if (VULKAN_LIBRARY)
            set(VULKAN_FOUND ON)
            message(STATUS "Found MoltenVK library.")
        endif()
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_USE_PLATFORM_METAL_EXT -DVK_EXAMPLE_XCODE_GENERATED")
endif(WIN32)

if (NOT VULKAN_FOUND)
    message(FATAL_ERROR "Could not find Vulkan library.")
else()
    message(STATUS ${Vulkan_LIBRARY})
endif()

# collect all executables
set(SOURCES
    src/libvox.cpp
)
#set(HEADERS
#    src/app.hpp
#)

# add executables
add_executable(libvox ${SOURCES} ${HEADERS})

target_link_libraries(libvox PRIVATE
    Vulkan::Vulkan
    glfw
    glm::glm
)

# add libraries
#target_include_directories(libvox PRIVATE
#    ${CMAKE_CURRENT_SOURCE_DIR}/include
#)
#target_link_libraries(libvox
#    "-framework Foundation"
#    "-framework Metal"
#    "-framework MetalKit"
#)