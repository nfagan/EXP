//
//  RenderLoop.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/4/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Render/RenderLoop.hpp>
#include <EXPGL/Model/Model.hpp>

EXP::RenderLoop::RenderLoop(std::shared_ptr<EXP::Renderer> renderer)
{
    this->renderer = renderer;
    this->should_loop.store(true);
    this->called_once_draw_ready.store(true);
}

void EXP::RenderLoop::Loop()
{
    while (should_loop.load())
    {
        user_loop();
        draw_ready();
        render_loop();
    }
}

void EXP::RenderLoop::CancelLoop()
{
    should_loop.store(false);
}

void EXP::RenderLoop::Queue(const std::vector<Model*> &models)
{
    queue_lock.lock();
    for (unsigned i = 0; i < models.size(); i++)
    {
        auto it = already_queued.find(models[i]->GetIdentifier().GetId());
        if (it == already_queued.end())
        {
            already_queued[models[i]->GetIdentifier().GetId()] = true;
            draw_queue.push_back(models[i]);
        }
    }
    queue_lock.unlock();
}

void EXP::RenderLoop::ClearQueue()
{
    queue_lock.lock();
    draw_queue.clear();
    already_queued.clear();
    queue_lock.unlock();
}

void EXP::RenderLoop::OnLoop(std::function<void(EXP::RenderLoop*)> on_loop)
{
    on_loop_lock.lock();
    this->on_loop = on_loop;
    on_loop_lock.unlock();
}

void EXP::RenderLoop::OnceDrawReady(std::function<void(EXP::RenderLoop*)> once_ready)
{
    while (!called_once_draw_ready.load())
    {
        //
    }
    this->once_draw_ready = once_ready;
    called_once_draw_ready.store(false);
}

void EXP::RenderLoop::user_loop()
{
    on_loop_lock.lock();
    on_loop(this);
    on_loop_lock.unlock();
}

void EXP::RenderLoop::render_loop()
{
    queue_lock.lock();
    for (unsigned i = 0; i < draw_queue.size(); i++)
    {
        renderer->Queue(draw_queue[i]);
    }
    queue_lock.unlock();
    renderer->Draw();
}

void EXP::RenderLoop::draw_ready()
{
    if (called_once_draw_ready.load()) return;
    once_draw_ready(this);
    called_once_draw_ready.store(true);
}

void EXP::RenderLoop::empty()
{
    //
}
