//
//  choice.hpp
//  EXP_examples
//
//  Created by Nick Fagan on 12/9/17.
//

#ifndef exp_choice_h
#define exp_choice_h

namespace ex2 {
    namespace states {
        namespace choice {
            
            using std::shared_ptr;
            using namespace EXP;
            
            auto render_function = [] (auto looper) {
                looper->ClearQueue();
                auto &gl = globals::gl::get();
                auto rsrc = gl.pipeline->GetResource();
                auto stim = rsrc->Get<Model>(gl.ids.triangle);
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
                state->SetTimeIn(EXP::Time::duration_ms(1000));
                state->ExitOnTimeExceeded();
                
                auto &gl = globals::gl::get();
                auto rsrc = gl.pipeline->GetResource();
                auto triangle = rsrc->CreateTriangle();
                auto fix_square = rsrc->Get<Model>(gl.ids.fixation_square);
                auto mat = triangle->GetMaterial();
                triangle->MakeLike(fix_square);
                mat->SetAlbedo(Colors::GREEN);
                triangle->SetMaterial(mat);
                
                gl.ids.triangle = triangle->GetUUID();
            };
        }
    }
}

#endif /* choice_h */
