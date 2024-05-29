#include <iostream>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include <metal-cpp/Metal.hpp>

#include "util/logger.cpp"

int main() {

    Logger logger;

    MTL::Device* device = MTL::CreateSystemDefaultDevice();

    logger.info("device init");

    return 0;
}