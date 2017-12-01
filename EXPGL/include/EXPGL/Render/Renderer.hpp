//
//  Renderer.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <glm/glm.hpp>
#include <EXPGL/Model/Model.hpp>
#include <EXPGL/Util/Colors.hpp>

namespace EXP {
    class Renderer
    {
    public:
        Renderer(EXP::RenderTarget *target);
        ~Renderer() = default;
        
        void Queue(EXP::Model *model);
        void Draw();
        
        glm::mat4 GetProjectionMatrix2D(const EXP::Rect<float> &window_rect) const;
        glm::mat4 GetProjectionMatrix3D(const EXP::Rect<float> &window_rect) const;
        
        void SetClearColor(glm::vec3 color);
    private:
        std::vector<EXP::Model*> models;
        EXP::RenderTarget *target;
        glm::vec3 clear_color = EXP::Colors::BLACK;
        
        void initialize(EXP::RenderTarget *target);
        void prepare_context(EXP::Window *window);
        void draw(EXP::Model *model, EXP::Window *window, unsigned index);
        void swap_buffers(EXP::Window *window);
    };
}

#endif /* Renderer_hpp */
