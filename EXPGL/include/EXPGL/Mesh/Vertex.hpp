//
//  Vertex.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/14/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <array>
#include <vector>

namespace EXP {
    struct Vertex
    {
    public:
        Vertex() = default;
        ~Vertex() = default;
        
        void set_position(std::array<float, 3> in_position);
        void set_uv(std::array<float, 2> in_uv);
        void set_normal(std::array<float, 3> in_normal);
        
        unsigned int size() const;
        unsigned int size_position() const;
        unsigned int size_uv() const;
        unsigned int size_normal() const;
        bool sizes_match(const Vertex &other) const;
        
        std::vector<float> get_interleaved_data() const;
    private:
        std::array<float, 3> position;
        std::array<float, 2> uv;
        std::array<float, 3> normal;
        
        unsigned int n_position = 0;
        unsigned int n_uv = 0;
        unsigned int n_normal = 0;
    };
}

#endif /* Vertex_hpp */
