//
//  Renderer.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Render/Renderer.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <EXPGL/Util/Common.hpp>

EXP::Renderer::Renderer(EXP::RenderTarget *target)
{
    initialize(target);
}

void EXP::Renderer::Draw(void)
{
    for (unsigned i = 0; i < target->Size(); ++i)
    {
        EXP::Window *window = target->GetWindow(i);
        prepare_context(window);
        for (unsigned j = 0; j < models.size(); ++j)
        {
            draw(models[j], window, i);
        }
    }
    for (unsigned i = 0; i < target->Size(); ++i)
    {
        swap_buffers(target->GetWindow(i));
    }
    models.clear();
}

void EXP::Renderer::Queue(EXP::Model *model)
{
    models.push_back(model);
}

void EXP::Renderer::SetClearColor(glm::vec3 color)
{
    clear_color = color;
}

glm::mat4 EXP::Renderer::GetProjectionMatrix2D(const Rect<float> &window_rect) const
{
    return glm::ortho(window_rect.get_left(), window_rect.get_right(),
                      window_rect.get_bottom(), window_rect.get_top());
}

glm::mat4 EXP::Renderer::GetProjectionMatrix3D(const EXP::Rect<float> &window_rect) const
{
    return GetProjectionMatrix2D(window_rect);
}

void EXP::Renderer::prepare_context(EXP::Window *window)
{
    window->MakeCurrent();
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void EXP::Renderer::draw(EXP::Model *model, EXP::Window *window, unsigned index)
{
    EXP::Shader *shader = model->GetShader();
    
    if (!shader)
    {
        std::cout << "Warning: No shader attached; model will not be drawn." << std::endl;
        return;
    }
    
    shader->Start();
    Rect<float> wrect = static_cast<Rect<float>>(*(window->GetRect()));
    Rect<float> srect = static_cast<Rect<float>>(target->GetFullRect());
    
    if (model->GetProjectionType() == EXP::util::projection_types::ORTHOGRAPHIC)
    {
        shader->SetMat4("projection", glm::mat4(1.0f));
        shader->SetMat4("view", GetProjectionMatrix2D(wrect));
    }
    else
    {
        //  3D not yet implemented
        throw std::runtime_error("Rendering with a perspective projection not yet implemented.");
    }
    
    shader->SetMat4("model", model->GetTransformationMatrix(srect));
    model->Draw(index);
    shader->Stop();
}

void EXP::Renderer::swap_buffers(EXP::Window *window)
{
    glfwSwapBuffers(window->GetWindow());
}

void EXP::Renderer::initialize(EXP::RenderTarget *target)
{
    target->GetPrimaryWindow()->MakeCurrent();
    this->target = target;
}
