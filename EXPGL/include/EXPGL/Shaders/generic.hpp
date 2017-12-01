//
//  generic.hpp
//  EXPGL
//
//  Created by Nick Fagan on 11/12/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef EXP_Generic_hpp
#define EXP_Generic_hpp

namespace EXP {
    namespace Shaders {
        namespace generic {
            static const char *fragment = R"(
                #version 330 core
            
                out vec4 FragColor;
                in vec2 TextureCoordinates;
            
                uniform bool albedo_use_texture;
                uniform sampler2D albedo_value_sampler2d;
                uniform vec3 albedo_value_vec3;
            
                void main()
                {
                    if (albedo_use_texture) {
                        FragColor = vec4(texture(albedo_value_sampler2d, TextureCoordinates).rgb, 1.0f);
                    } else {
                        FragColor = vec4(albedo_value_vec3, 1.0f);
                    }
                })";
            
            static const char *vertex = R"(
                #version 330 core
                layout (location = 0) in vec3 position;
                layout (location = 1) in vec2 tex_coords;
            
                uniform mat4 model;
                uniform mat4 view;
                uniform mat4 projection;
            
                out vec2 TextureCoordinates;
            
                void main()
                {
                    TextureCoordinates = tex_coords;
                    gl_Position = projection * view * model * vec4(position, 1.0f);
                })";
        }
    }
}

#endif
