#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.hpp>

#include "model/vertex_data.hpp"

#pragma region Declarations {

    class CoreRender {

        public:

            CoreRender(MTL::Device* device);

            ~CoreRender();

            void build_shaders();

            void build_buffers();

            void draw(MTK::View* view);

        private:

            MTL::Device* _device;
            MTL::CommandQueue* _cmd_queue;
            MTL::RenderPipelineState* _render_pipeline_state;
            MTL::Buffer* _vrtx_pos_buff;
            MTL::Buffer* _vrtx_colors_buff;

    };

    class CoreViewDelegate : public MTK::ViewDelegate {

        public:

            CoreViewDelegate(MTL::Device* device);

            virtual ~CoreViewDelegate() override;

            virtual void drawInMTKView(MTK::View* view) override;

        private:

            CoreRender* _core_render;

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
            CoreViewDelegate* _core_view_delegate = nullptr;

    };

#pragma endregion Declarations }