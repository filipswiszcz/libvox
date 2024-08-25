#include "app.hpp"

#pragma mark - CoreRender
#pragma region CoreRender {

    CoreRender::CoreRender(MTL::Device* device) : _device(device -> retain()) {
        _cmd_queue = _device -> newCommandQueue();
    }

    CoreRender::~CoreRender() {
        _cmd_queue -> release();
        _device -> release();
    }

    void CoreRender::draw(MTK::View* view) {

        NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc() -> init();

        MTL::CommandBuffer* cmd_buff = _cmd_queue -> commandBuffer();
        MTL::RenderPassDescriptor* pass_dsc = view -> currentRenderPassDescriptor();
        MTL::RenderCommandEncoder* cmd_encoder = cmd_buff -> renderCommandEncoder(pass_dsc);

        cmd_encoder -> endEncoding();

        cmd_buff -> presentDrawable(view -> currentDrawable());
        cmd_buff -> commit();

        pool -> release();
    }

#pragma region }

#pragma mark - CoreViewDelegate
#pragma region CoreViewDelegate {

    CoreViewDelegate::CoreViewDelegate(MTL::Device* device) : MTK::ViewDelegate(), _core_render(new CoreRender(device)) {}

    CoreViewDelegate::~CoreViewDelegate() {
        delete _core_render;
    }

    void CoreViewDelegate::drawInMTKView(MTK::View* view) {
        _core_render -> draw(view);
    }

#pragma endregion CoreViewDelegate }

#pragma mark - CoreApplicationDelegate
#pragma region CoreApplicationDelegate {

    CoreApplicationDelegate::~CoreApplicationDelegate() {

        _view -> release();
        _window -> release();
        _device -> release();

        delete _core_view_delegate;
    }

    NS::Menu* CoreApplicationDelegate::getMenuBar() {

        using NS::UTF8StringEncoding;

        NS::Menu* main_menu = NS::Menu::alloc() -> init();
        NS::Menu* app_menu = NS::Menu::alloc() -> init(NS::String::string("libvox", UTF8StringEncoding));
        NS::MenuItem* app_menu_item = NS::MenuItem::alloc() -> init();

        NS::String* app_name = NS::RunningApplication::currentApplication() -> localizedName();
        NS::String* quit_item_name = NS::String::string("Quit ", UTF8StringEncoding) -> stringByAppendingString(app_name);

        SEL app_quit_action = NS::MenuItem::registerActionCallback("app_quit", [](void*, SEL, const NS::Object* app) {
            auto selected_app = NS::Application::sharedApplication();
            selected_app -> terminate(app);
        });

        NS::MenuItem* app_quit_item = app_menu -> addItem(quit_item_name, app_quit_action, NS::String::string("q", UTF8StringEncoding));
        app_quit_item -> setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

        app_menu_item -> setSubmenu(app_menu);

        NS::MenuItem* window_menu_item = NS::MenuItem::alloc() -> init();
        NS::Menu* window_menu = NS::Menu::alloc() -> init(NS::String::string("Window", UTF8StringEncoding));

        SEL menu_close_action = NS::MenuItem::registerActionCallback("window_close", [](void*, SEL, const NS::Object* app) {
            auto selected_app = NS::Application::sharedApplication();
            selected_app -> windows() -> object<NS::Window>(0) -> close();
        });

        NS::MenuItem* window_close_item = window_menu -> addItem(NS::String::string("Close window", UTF8StringEncoding), menu_close_action, NS::String::string("w", UTF8StringEncoding));
        window_close_item -> setKeyEquivalentModifierMask(NS::EventModifierFlagCommand);

        window_menu_item -> setSubmenu(window_menu);

        main_menu -> addItem(app_menu_item);
        main_menu -> addItem(window_menu_item);

        app_menu_item -> release();
        window_menu_item -> release();
        app_menu -> release();
        window_menu -> release();

        return main_menu -> autorelease();
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
            {800.0, 600.0}
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

        _core_view_delegate = new CoreViewDelegate(_device);

        _view -> setDelegate(_core_view_delegate);

        _window -> setContentView(_view);
        _window -> setTitle(NS::String::string("Powered by xycorp", NS::StringEncoding::UTF8StringEncoding));
        _window -> makeKeyAndOrderFront(nullptr);

        NS::Application* app = reinterpret_cast<NS::Application*>(notf -> object());
        app -> activateIgnoringOtherApps(true);
    }

    bool CoreApplicationDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application* app) {return true;}

#pragma endregion CoreApplicationDelegate }

#pragma mark - CoreViewDelegate
#pragma region CoreViewDelegate {

    CoreViewDelegate::CoreViewDelegate(MTL::Device* device) : MTK::ViewDelegate(), _core_render(new CoreRender(device)) {}

    CoreViewDelegate::~CoreViewDelegate() {
        delete _core_render;
    }

    void CoreViewDelegate::drawInMTKView(MTK::View* view) {
        _core_render -> draw(view);
    }

#pragma endregion CoreViewDelegate }

#pragma mark - CoreRender
#pragma region CoreRender {

    CoreRender::CoreRender(MTL::Device* device) : _device(device -> retain()) {
        _cmd_queue = _device -> newCommandQueue();

        this -> build_shaders();
        this -> build_buffers();
    }

    CoreRender::~CoreRender() {
        _vrtx_pos_buff -> release();
        _vrtx_colors_buff -> release();
        _render_pipeline_state -> release();
        _cmd_queue -> release();
        _device -> release();
    }

    void CoreRender::build_shaders() {

        using NS::StringEncoding::UTF8StringEncoding;

        const char* shader_source = R"(
            #include <metal_stdlib>

            using namespace metal;

            
        )";
    }

#pragma endregion CoreRender }