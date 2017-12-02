//
//  GLPipeline.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/18/17.
//

#ifndef GLPipeline_hpp
#define GLPipeline_hpp

#include <EXPGL/Context/GLContextManager.hpp>
#include <EXPGL/Context/Window.hpp>
#include <EXPGL/Render/Renderer.hpp>
#include <EXPGL/Render/RenderLoop.hpp>
#include <EXPGL/Loaders/GLResourceManager.hpp>
#include <memory>
#include <cassert>

namespace EXP {
class GLPipeline
{
public:
    GLPipeline(std::shared_ptr<GLContextManager> manager);
    ~GLPipeline() = default;
    
    void Begin(int index = 0);
    void Begin(int index, int width, int height);
    
    std::shared_ptr<Renderer> GetRenderer() const;
    std::shared_ptr<RenderLoop> GetRenderLoop() const;
    std::shared_ptr<GLResourceManager> GetResource() const;
    std::shared_ptr<RenderTarget> GetTarget() const;
private:
    bool is_initialized;
    std::shared_ptr<GLContextManager> context;
    std::shared_ptr<RenderTarget> target;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<GLResourceManager> resource;
    std::shared_ptr<RenderLoop> loop;
    
    void ensure_initialized(void) const;
    void begin(std::shared_ptr<RenderTarget> target);
};
}

#endif /* GLPipeline_hpp */
