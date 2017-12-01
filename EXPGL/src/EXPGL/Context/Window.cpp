//
//  Window.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/20/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Context/Window.hpp>

EXP::Window::Window() {};

EXP::Window::Window(GLFWmonitor* monitor, unsigned monitor_index, unsigned id, EXP::Window *other)
{
    this->monitor = monitor;
    this->monitor_index = monitor_index;
    this->id = id;
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    unsigned width = mode->width;
    unsigned height = mode->height;
    create_window(monitor, width, height, other);
    is_fullscreen = true;
}

EXP::Window::Window(GLFWmonitor* monitor, unsigned monitor_index, unsigned id,
                    unsigned width, unsigned height, EXP::Window *other)
{
    this->monitor = monitor;
    this->monitor_index = monitor_index;
    this->id = id;
    create_window(NULL, width, height, other);
    is_fullscreen = false;
}

EXP::Window::~Window()
{
    delete rect;
}

void EXP::Window::Close()
{
    glfwSetWindowShouldClose(window, true);
}

void EXP::Window::MakeCurrent()
{
    glfwMakeContextCurrent(window);
}

void EXP::Window::Focus()
{
    glfwFocusWindow(window);
}

void EXP::Window::SetPosition(int x, int y)
{
    glfwSetWindowPos(window, x, y);
}

void EXP::Window::create_window(GLFWmonitor *monitor, unsigned width, unsigned height, Window *other)
{
    if (!other)
    {
        window = glfwCreateWindow(width, height, "", monitor, NULL);
    }
    else
    {
        window = glfwCreateWindow(width, height, "", monitor, other->GetWindow());
    }
    create_rect(width, height);
}

void EXP::Window::create_rect(unsigned int width, unsigned int height)
{
    rect = new Rect<int>(0, 0, width, height);
}

void EXP::Window::ShiftRect(int x, int y)
{
    this->rect->shift_xy(x, y);
}
