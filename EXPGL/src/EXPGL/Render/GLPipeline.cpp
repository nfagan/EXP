//
//  GLPipeline.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/30/17.
//

#include <EXPGL/Render/GLPipeline.hpp>

EXP::GLPipeline::GLPipeline(GLContextManager *manager) : context(manager)
{
    is_initialized = false;
}

void EXP::GLPipeline::Begin(int index)
{
    assert(context);
    target = context->CreateRenderTarget(context->OpenWindow(index, nullptr));
    begin(target);
    
}
void EXP::GLPipeline::Begin(int index, int width, int height)
{
    assert(context);
    target = context->CreateRenderTarget(context->OpenWindow(index, width, height, nullptr));
    begin(target);
}

std::shared_ptr<EXP::Renderer> EXP::GLPipeline::GetRenderer() const
{
    ensure_initialized();
    return renderer;
}

std::shared_ptr<EXP::RenderLoop> EXP::GLPipeline::GetRenderLoop() const
{
    ensure_initialized();
    return loop;
}

std::shared_ptr<EXP::GLResourceManager> EXP::GLPipeline::GetResource() const
{
    ensure_initialized();
    return resource;
}

EXP::RenderTarget* EXP::GLPipeline::GetTarget() const
{
    ensure_initialized();
    return target;
}

void EXP::GLPipeline::ensure_initialized(void) const
{
    if (!is_initialized)
    {
        throw std::runtime_error("A call to begin() must precede item access.");
    }
}

void EXP::GLPipeline::begin(RenderTarget *target)
{
    resource = std::make_shared<GLResourceManager>(target);
    renderer = std::make_shared<Renderer>(target);
    loop = std::make_shared<RenderLoop>(renderer);
    is_initialized = true;
}
