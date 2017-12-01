//
//  RenderTarget.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/21/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Render/RenderTarget.hpp>
#include <string>
#include <assert.h>

EXP::RenderTarget::RenderTarget(std::vector<EXP::Window*> windows)
{
    assert(windows.size() > 0);
    this->windows = windows;
    this->full_rect = new EXP::Rect<int>(0, 0, 0, 0);
    set_window_titles();
    glfwPollEvents();
    windows[0]->Focus();
    set_window_offsets();
}

EXP::RenderTarget::~RenderTarget()
{
    delete full_rect;
}

void EXP::RenderTarget::set_window_titles()
{
    for (unsigned i = 0; i < windows.size(); ++i)
    {
        if (!windows[i]->is_fullscreen)
        {
            std::string title = std::string("Window ") + std::to_string(i);
            glfwSetWindowTitle(windows[i]->GetWindow(), title.c_str());
        }
    }
}

EXP::Rect<int> EXP::RenderTarget::GetFullRect() const
{
    return *full_rect;
}

unsigned EXP::RenderTarget::Size() const
{
    return windows.size();
}

EXP::Window* EXP::RenderTarget::GetWindow(unsigned index) const
{
    return windows[index];
}

EXP::Window* EXP::RenderTarget::GetPrimaryWindow() const
{
    return GetWindow(0);
}

void EXP::RenderTarget::SetTileType(TILING tile_type)
{
    this->tile_type = tile_type;
}

void EXP::RenderTarget::set_window_offsets()
{
    //  vertical layouts to come
    assert(tile_type == HORIZONTAL);
    
    EXP::Rect<int> *first = windows[0]->GetRect();
    first->clone_into(full_rect);
    
    windows[0]->SetPosition(first->get_left(), 0);
    
    for (unsigned i = 1; i < windows.size(); ++i)
    {
        Rect<int> *current = windows[i]->GetRect();
        
        if (tile_type == HORIZONTAL)
        {
            int width = current->get_width();
            
            full_rect->set_right(full_rect->get_right() + width);
            current->set_right(full_rect->get_right());
            current->set_left(current->get_right() - width);
            
            windows[i]->SetPosition(current->get_left(), 0);
        }
        else
        {
            //  vertical layouts to come
            assert(false);
        }
    }
}


