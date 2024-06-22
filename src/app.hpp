#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#pragma region Declarations {

    class CoreRender {

        public:

            CoreRender(MTL::Device* device);

            ~CoreRender();

            void draw(MTK::View* view);

        private:

            MTL::Device* _device;
            MTL::CommandQueue* _cmdQueue;

    };

    class CoreViewDelegate : public MTK::ViewDelegate {

        public:

            CoreViewDelegate(MTL::Device* device);

            virtual ~CoreViewDelegate() override;

            virtual void drawInMTKView(MTK::View* view) override;

        private:

            CoreRender* _coreRender;

    };

    class CoreApplicationDelegate : public NS::ApplicationDelegate {

        public:

            ~CoreApplicationDelegate();

            NS::Menu* getMenuBar();

            virtual void applicationWillFinishLaunching(NS::Notification* notf) override;

            virtual void applicationDidFinishLaunching(NS::Notification* notf) override;

            virtual bool applicationShouldTerminateAfterLastWindowClosed(class NS::Application* app) override;

        private:

            NS::Window* _window;
            MTK::View* _view;
            MTL::Device* _device;
            CoreViewDelegate* _coreViewDelegate = nullptr;

    };

#pragma endregion Declarations }