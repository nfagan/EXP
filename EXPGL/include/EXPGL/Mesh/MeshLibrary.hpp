//
//  MeshLibrary.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/14/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef MeshLibrary_hpp
#define MeshLibrary_hpp

#include <EXPGL/Mesh/Mesh.hpp>
#include <EXPGL/Mesh/Vertex.hpp>
#include <array>
#include <cmath>

namespace EXP {
    namespace MeshLibrary {
        
        static const void make_quad(Mesh *mesh)
        {
            using std::array;
            
            static const float vertex_data[48] = {
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
            };
            
            for (unsigned i = 0; i < 6; ++i)
            {
                Vertex vertex;
                float x = vertex_data[i*8+0];
                float y = vertex_data[i*8+1];
                float z = vertex_data[i*8+2];
                float u = vertex_data[i*8+3];
                float v = vertex_data[i*8+4];
                float nx = vertex_data[i*8+5];
                float ny = vertex_data[i*8+6];
                float nz = vertex_data[i*8+7];
                
                vertex.set_position(array<float, 3>{{x, y, z}});
                vertex.set_uv(array<float, 2>{{u, v}});
                vertex.set_normal(array<float, 3>{{nx, ny, nz}});
                
                mesh->AddVertex(vertex);
                mesh->SetTopology(Mesh::TRIANGLES);
            }
        }
        
        static const void make_triangle(Mesh *mesh)
        {
            using std::array;
            
            static const float vertex_data[24] = {
                -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
            };
            
            for (unsigned i = 0; i < 3; ++i)
            {
                Vertex vertex;
                float x = vertex_data[i*8+0];
                float y = vertex_data[i*8+1];
                float z = vertex_data[i*8+2];
                float u = vertex_data[i*8+3];
                float v = vertex_data[i*8+4];
                float nx = vertex_data[i*8+5];
                float ny = vertex_data[i*8+6];
                float nz = vertex_data[i*8+7];
                
                vertex.set_position(array<float, 3>{{x, y, z}});
                vertex.set_uv(array<float, 2>{{u, v}});
                vertex.set_normal(array<float, 3>{{nx, ny, nz}});
                
                mesh->AddVertex(vertex);
                mesh->SetTopology(Mesh::TRIANGLES);
            }
        }
        
        static const void make_sphere(Mesh *mesh, int vertex_count)
        {
            using std::array;
            
            static const float PI = 3.14159265359;
            
            for (unsigned int i=0; i<vertex_count; i++) {
                for (unsigned int j=0; j<vertex_count; j++) {
                    
                    float x_segment = float(j)/float(vertex_count-1);
                    float y_segment = float(i)/float(vertex_count-1);
                    
                    float x_pos = std::cos(x_segment * 2.0f * PI) * std::sin(y_segment * PI);
                    float y_pos = std::cos(y_segment * PI);
                    float z_pos = std::sin(x_segment * 2.0f * PI) * std::sin(y_segment * PI);
                    
                    Vertex vertex;
                    
                    vertex.set_position(array<float, 3>{{x_pos, y_pos, 0.0f}});
                    vertex.set_uv(array<float, 2>{{x_segment, y_segment}});
                    vertex.set_normal(array<float, 3>{{x_pos, y_pos, z_pos}});
                    
                    mesh->AddVertex(vertex);
                }
            }
            
            unsigned int first_index = 0;
            unsigned int next_index = first_index + vertex_count;
            std::vector<unsigned int> indices;
            unsigned int index_stp = 0;
            bool should_proceed = true;
            
            while (should_proceed)
            {
                indices.push_back(first_index);
                indices.push_back(next_index);
                index_stp += 2;
                
                should_proceed = next_index != ((vertex_count * vertex_count) - 1);
                
                if (index_stp > 0 && (next_index+1) % vertex_count == 0 && should_proceed) {
                    indices.push_back(next_index);
                    indices.push_back(first_index+1);
                    index_stp += 2;
                }
                
                first_index++;
                next_index++;
            }
            
            mesh->SetTopology(Mesh::TRIANGLE_STRIP);
            mesh->SetIndices(indices);
        }
    }
}

#endif /* MeshLibrary_hpp */
