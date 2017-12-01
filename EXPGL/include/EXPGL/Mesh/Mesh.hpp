//
//  Mesh.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <EXPGL/Render/RenderTarget.hpp>
#include <EXPGL/Resource/GLResourcePrimitive.hpp>
#include <vector>
#include <EXPGL/Mesh/Vertex.hpp>

namespace EXP {
    class Mesh : public GLResourcePrimitive
    {
    public:        
        enum TOPOLOGY {
            TRIANGLES,
            TRIANGLE_STRIP
        };
        
        Mesh();
        virtual ~Mesh();

        virtual void SetTopology(TOPOLOGY topology);
        virtual void SetIndices(std::vector<unsigned int> indices);
        virtual void AddVertex(Vertex vertex);
        virtual void Initialize(EXP::RenderTarget *target);
        virtual void Finalize(EXP::RenderTarget *target);
        virtual bool IsInitialized() const;
        virtual bool IsFinalized() const;
        virtual void Draw(unsigned index) const;
        virtual void Bind(unsigned index) const;
        virtual void Unbind() const;
    protected:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        
        unsigned *vaos;
        unsigned vbo;
        unsigned ebo;
        int n_vaos;
        int n_fragments;
        TOPOLOGY topology = TRIANGLES;
        bool is_initialized = false;
        bool is_finalized = false;
        
        std::vector<float> get_interleaved_data() const;
        void create_vao(unsigned int index);
    };
}

#endif /* Mesh_hpp */
