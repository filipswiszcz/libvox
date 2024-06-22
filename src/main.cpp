#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include "util/logger.cpp"

#include "app.hpp"

int main() {

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc() -> init();

    CoreApplicationDelegate coreApp;

    NS::Application* sharedApp = NS::Application::sharedApplication();
    sharedApp -> setDelegate(&coreApp);
    sharedApp -> run();

    pool -> release();

    return 0;
}