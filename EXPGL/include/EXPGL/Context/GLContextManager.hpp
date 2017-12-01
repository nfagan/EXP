//
//  GLContextManager.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/20/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef GLContextManager_hpp
#define GLContextManager_hpp

#include <gl.h>
#include <stdio.h>
#include <vector>
#include <EXPGL/Context/Window.hpp>
#include <EXPGL/Render/RenderTarget.hpp>

namespace EXP {
    
    class GLContextManager
    {
    public:
        GLContextManager();
        ~GLContextManager();
        
        bool DidInitialize();
        
        Window* OpenWindow(unsigned index, Window *other);
        Window* OpenWindow(unsigned index, unsigned width, unsigned height, Window *other);
        void CloseWindow(Window *window);
        void CloseTarget(RenderTarget *target);
        void PollEvents();
        
        RenderTarget* CreateRenderTarget(Window *window);
        RenderTarget* CreateRenderTarget(std::vector<EXP::Window*> windows);
    private:
        int init_status;
        
        void init_context(void);
        void init_monitors(void);
        
        GLFWmonitor** monitors;
        int n_monitors;
        bool *has_fullscreen_window;
        
        std::vector<Window*> windows;
        std::vector<RenderTarget*> render_targets;
        
        void validate_index(unsigned index);
        void register_window(Window *window);
    };
}

#endif /* GLContextManager_hpp */
