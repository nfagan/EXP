//
//  ShaderLibrary.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/30/17.
//

#ifndef ShaderLibrary_h
#define ShaderLibrary_h

#include <vector>
#include <string>
#include <EXPGL/Render/Shader.hpp>
#include <EXPGL/Shaders/generic.hpp>

namespace EXP {
    namespace ShaderLibrary {
        
        namespace {
            static const void make_shader_(Shader *shader, const std::vector<const char*> &codes,
                              const std::vector<Shader::SHADER_TYPES> &shader_types)
            {
                if (codes.size() != shader_types.size())
                {
                    throw std::logic_error("Number of code elements must match number of shader types.");
                }
                
                bool compile_result, link_result;
                
                for (unsigned i = 0; i < codes.size(); ++i)
                {
                    compile_result = shader->AttachFromSource(codes[i], shader_types[i]);
                    
                    if (!compile_result)
                    {
                        throw std::runtime_error("Failed to compile shader.");
                    }
                }
                
                link_result = shader->Link();
                
                if (!link_result)
                {
                    throw std::runtime_error("Failed to link shader program.");
                }
            }
        }
        
        static const void make_generic(Shader *shader)
        {
            std::vector<const char*> codes;
            std::vector<Shader::SHADER_TYPES> shader_types;
            
            codes.push_back(Shaders::generic::vertex);
            codes.push_back(Shaders::generic::fragment);
            
            shader_types.push_back(Shader::VERTEX);
            shader_types.push_back(Shader::FRAGMENT);
            
            make_shader_(shader, codes, shader_types);
        }
        
    }
}

#endif /* ShaderLibrary_h */
