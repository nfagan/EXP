//
//  RenderTarget.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/21/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef RenderTarget_hpp
#define RenderTarget_hpp

#include <vector>
#include <EXPGL/Context/Window.hpp>
#include <EXPGL/Util/Rect.hpp>

namespace EXP {
    
    class RenderTarget
    {
    public:
        enum TILING {
            VERTICAL,
            HORIZONTAL
        };
        
        RenderTarget(std::vector<EXP::Window*> windows);
        ~RenderTarget();
        
        void SetTileType(TILING tile_type);
        
        EXP::Rect<int> GetFullRect() const;
        EXP::Window* GetPrimaryWindow() const;
        EXP::Window* GetWindow(unsigned i) const;
        unsigned Size() const;
        
    private:
        std::vector<EXP::Window*> windows;
        EXP::Rect<int> *full_rect;
        TILING tile_type = HORIZONTAL;
        
        void set_window_titles(void);
        void set_window_offsets(void);
    };
}

#endif /* RenderTarget_hpp */
