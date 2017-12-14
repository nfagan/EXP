//
//  mistake.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/9/17.
//

#ifndef mistake_h
#define mistake_h

namespace ex2 {
    namespace states {
        namespace mistake {
            
            using std::shared_ptr;
            using namespace EXP;
            
            auto render_function = [] (auto looper) {
                looper->ClearQueue();
                auto &gl = globals::gl::get();
                auto rsrc = gl.pipeline->GetResource();
                auto stim = rsrc->Get<Model>(gl.ids.error_square);
                looper->Queue(stim);
            };
            
            auto on_entry = [] (auto state) {
                auto &gl = globals::gl::get();
                gl.pipeline->GetRenderLoop()->OnceDrawReady(render_function);
            };
            
            auto on_exit = [] (auto state) {
                auto &task = globals::task::get();
                state->Next(task.ids.fixation);
            };
            
            auto setup = [] (auto state) {
                state->OnEntry(on_entry);
                state->OnExit(on_exit);
                state->SetTimeIn(Time::duration_ms(1000));
                state->ExitOnTimeExceeded();
                
                auto &gl = globals::gl::get();
                auto rsrc = gl.pipeline->GetResource();
                auto error_square = rsrc->CreateRectangle();
                auto mat = error_square->GetMaterial();
//                auto tex = rsrc->GetTexture(file::get_full_path("../") + "/res/textures/tex1.png");
                auto tex = Colors::RED;
                auto fix_square = rsrc->Get<Model>(gl.ids.fixation_square);
                
                mat->SetAlbedo(tex);
                error_square->MakeLike(fix_square);
                error_square->SetMaterial(mat);
                error_square->SetScale(glm::vec2(50.0f));
                
                gl.ids.error_square = error_square->GetUUID();
            };
        }
        
    }
}


#endif /* mistake_h */
