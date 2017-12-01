//
//  Window.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/20/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include <stdio.h>
#include <EXPGL/Util/Rect.hpp>
#include <gl.h>

namespace EXP {
    class Window
    {
    public:
        bool is_fullscreen;
        
        Window();
        Window(GLFWmonitor* monitor, unsigned monitor_index, unsigned id, Window *other);
        Window(GLFWmonitor* monitor, unsigned index, unsigned id, unsigned width, unsigned height, Window *other);
        
        ~Window();
        
        void Close(void);
        void MakeCurrent(void);
        void Focus(void);
        void SetPosition(int x, int y);
        
        GLFWwindow* GetWindow() const { return window; };
        unsigned GetMonitorIndex() const { return monitor_index; };
        GLFWmonitor* GetMonitor() const { return monitor; };
        unsigned GetId() const { return id; };
        Rect<int>* GetRect() const { return rect; };
        
        void ShiftRect(int x, int y);
    private:
        EXP::Rect<int> *rect = nullptr;
        GLFWwindow *window = nullptr;
        GLFWmonitor *monitor = nullptr;
        unsigned monitor_index;
        unsigned id;
        
        void create_window(GLFWmonitor *monitor, unsigned width, unsigned height, Window *other);
        void create_rect(unsigned width, unsigned height);
    };
}

#endif
