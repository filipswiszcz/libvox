#include "app.hpp"

#pragma mark - CoreRender
#pragma region CoreRender {

    CoreRender::CoreRender(MTL::Device* device) : _device(device -> retain()) {
        _cmdQueue = _device -> newCommandQueue();
    }

    CoreRender::~CoreRender() {
        _cmdQueue -> release();
        _device -> release();
    }

    void CoreRender::draw(MTK::View* view) {

        NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc() -> init();

        MTL::CommandBuffer* cmdBuff = _cmdQueue -> commandBuffer();
        MTL::RenderPassDescriptor* passDsc = view -> currentRenderPassDescriptor();
        MTL::RenderCommandEncoder* cmdEncoder = cmdBuff -> renderCommandEncoder(passDsc);

        cmdEncoder -> endEncoding();

        cmdBuff -> presentDrawable(view -> currentDrawable());
        cmdBuff -> commit();

        pool -> release();
    }

#pragma region }

#pragma mark - CoreViewDelegate
#pragma region CoreViewDelegate {

    CoreViewDelegate::CoreViewDelegate(MTL::Device* device) : MTK::ViewDelegate(), _coreRender(new CoreRender(device)) {}

    CoreViewDelegate::~CoreViewDelegate() {
        delete _coreRender;
    }

    void CoreViewDelegate::drawInMTKView(MTK::View* view) {
        _coreRender -> draw(view);
    }

#pragma endregion CoreViewDelegate }

#pragma mark - CoreApplicationDelegate
#pragma region CoreApplicationDelegate {

    CoreApplicationDelegate::~CoreApplicationDelegate() {

        _view -> release();
        _window -> release();
        _device -> release();

        delete _coreViewDelegate;
    }

    NS::Menu* CoreApplicationDelegate::getMenuBar() {

        using NS::UTF8StringEncoding;

        NS::Menu* mainMenu = NS::Menu::alloc() -> init();
        NS::Menu* appMenu = NS::Menu::alloc() -> init(NS::String::string("libvox", UTF8StringEncoding));
        NS::MenuItem* appMenuItem = NS::MenuItem::alloc() -> init();

        NS::String* appName = NS::RunningApplication::currentApplication() -> localizedName();
        NS::String* quitItemName = NS::String::string("quit", UTF8StringEncoding) -> stringByAppendingString(appName);

        SEL appQuitAction = NS::MenuItem::registerActionCallback("appQuit", [](void*, SEL, const NS::Object* app) {
            auto selectedApp = NS::Application::sharedApplication();
            selectedApp -> terminate(app);
        });

        NS::MenuItem* appQuitItem = appMenu -> addItem(quitItemName, appQuitAction, NS::String::string("q", UTF8StringEncoding));
        appQuitItem -> setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

        appMenuItem -> setSubmenu(appMenu);

        NS::MenuItem* windowMenuItem = NS::MenuItem::alloc() -> init();
        NS::Menu* windowMenu = NS::Menu::alloc() -> init(NS::String::string("window", UTF8StringEncoding));

        SEL menuCloseAction = NS::MenuItem::registerActionCallback("windowClose", [](void*, SEL, const NS::Object* app) {
            auto selectedApp = NS::Application::sharedApplication();
            selectedApp -> windows() -> object<NS::Window>(0) -> close();
        });

        NS::MenuItem* windowCloseItem = windowMenu -> addItem(NS::String::string("close window", UTF8StringEncoding), menuCloseAction, NS::String::string("w", UTF8StringEncoding));
        windowCloseItem -> setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

        windowMenuItem -> setSubmenu(windowMenu);

        mainMenu -> addItem(appMenuItem);
        mainMenu -> addItem(windowMenuItem);

        appMenuItem -> release();
        windowMenuItem -> release();
        appMenu -> release();
        windowMenu -> release();

        return mainMenu -> autorelease();
    }

    void CoreApplicationDelegate::applicationWillFinishLaunching(NS::Notification* notf) {
        
        NS::Menu* menu = this -> getMenuBar();
        NS::Application* app = reinterpret_cast<NS::Application*>(notf -> object());

        app -> setMainMenu(menu);
        app -> setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
    }

    void CoreApplicationDelegate::applicationDidFinishLaunching(NS::Notification* notf) {

        CGRect frame = (CGRect) {
            {100.0, 100.0},
            {1024.0, 1024.0}
        };

        _window = NS::Window::alloc() -> init(
            frame,
            NS::WindowStyleMaskClosable|NS::WindowStyleMaskTitled,
            NS::BackingStoreBuffered,
            false
        );

        _device = MTL::CreateSystemDefaultDevice();

        _view = MTK::View::alloc() -> init(frame, _device);
        _view -> setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);
        _view -> setClearColor(MTL::ClearColor::Make(0.0, 0.0, 0.0, 1.0));
        _view -> setDepthStencilPixelFormat(MTL::PixelFormat::PixelFormatDepth16Unorm);
        _view -> setClearDepth(1.0f);

        _coreViewDelegate = new CoreViewDelegate(_device);

        _view -> setDelegate(_coreViewDelegate);

        _window -> setContentView(_view);
        _window -> setTitle(NS::String::string("Powered by xycorp", NS::StringEncoding::UTF8StringEncoding));
        _window -> makeKeyAndOrderFront(nullptr);

        NS::Application* app = reinterpret_cast<NS::Application*>(notf -> object());
        app -> activateIgnoringOtherApps(true);
    }

    bool CoreApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application* app) {return true;}

#pragma endregion CoreApplicationDelegate }