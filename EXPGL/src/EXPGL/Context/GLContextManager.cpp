//
//  GLContextManager.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/20/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Context/GLContextManager.hpp>
#include <assert.h>

EXP::GLContextManager::GLContextManager()
{
    init_context();
    init_monitors();
}

void EXP::GLContextManager::init_context()
{
    init_status = glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_NONE);
}

void EXP::GLContextManager::init_monitors()
{
    monitors = glfwGetMonitors(&n_monitors);
    has_fullscreen_window = new bool[n_monitors];
    for (int i = 0; i < n_monitors; ++i)
    {
        has_fullscreen_window[i] = false;
    }
}

EXP::GLContextManager::~GLContextManager()
{
    for (unsigned i = 0; i < windows.size(); ++i)
    {
        delete windows[i];
    }
    for (unsigned i = 0; i < render_targets.size(); ++i)
    {
        delete render_targets[i];
    }
    delete[] has_fullscreen_window;
}

bool EXP::GLContextManager::DidInitialize()
{
    return init_status == GLFW_TRUE;
}

void EXP::GLContextManager::register_window(EXP::Window *window)
{
    if (windows.size() == 0)
    {
        window->MakeCurrent();
        int result = gladLoadGL();
        assert(result);
    }
    windows.push_back(window);
}

void EXP::GLContextManager::CloseWindow(EXP::Window *window)
{
    window->Close();
    windows.erase(windows.begin() + window->GetId());
    unsigned monitor_index = window->GetMonitorIndex();
    if (has_fullscreen_window[monitor_index])
    {
        has_fullscreen_window[monitor_index] = false;
    }
}

EXP::Window* EXP::GLContextManager::OpenWindow(unsigned index, unsigned width, unsigned height, EXP::Window *other)
{
    validate_index(index);
    Window* window = new Window(monitors[index], index, windows.size(), width, height, other);
    register_window(window);
    return window;
}

EXP::Window* EXP::GLContextManager::OpenWindow(unsigned index, EXP::Window *other)
{
    validate_index(index);
    has_fullscreen_window[index] = true;
    Window* window = new Window(monitors[index], index, windows.size(), other);
    register_window(window);
    return window;
}

void EXP::GLContextManager::validate_index(unsigned index)
{
    assert(index < n_monitors);
    assert(!has_fullscreen_window[index]);
}

EXP::RenderTarget* EXP::GLContextManager::CreateRenderTarget(EXP::Window *window)
{
    std::vector<EXP::Window*> windows = { window };
    return CreateRenderTarget(windows);
}

EXP::RenderTarget* EXP::GLContextManager::CreateRenderTarget(std::vector<EXP::Window*> windows)
{
    RenderTarget *target = new EXP::RenderTarget(windows);
    render_targets.push_back(target);
    return target;
}

void EXP::GLContextManager::CloseTarget(EXP::RenderTarget *target)
{
    for (unsigned i = 0; i < target->Size(); ++i)
    {
        CloseWindow(target->GetWindow(i));
    }
}

void EXP::GLContextManager::PollEvents()
{
    glfwPollEvents();
}

