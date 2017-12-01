//
//  Model.hpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <atomic>
#include <EXPGL/Util/Common.hpp>
#include <EXPGL/Mesh/Mesh.hpp>
#include <EXPGL/Material/Material.hpp>
#include <EXPGL/Texture/Texture.hpp>
#include <EXPGL/Render/Shader.hpp>
#include <EXPGL/Resource/GLResourcePrimitive.hpp>

namespace EXP {
    class Model : public GLResourcePrimitive
    {
        
        friend class ModelLoader;
    public:
        
        Model(EXP::Mesh *mesh, EXP::Material *material);
        ~Model() = default;
        
        void SetShader(EXP::Shader *shader);
        void SetMaterial(EXP::Material *material);
        void SetMesh(EXP::Mesh *mesh);
        void SetPosition(glm::vec3 position);
        void SetPosition(glm::vec2 position);
        void SetRotation(glm::vec3 rotation);
        void SetRotation(glm::vec2 rotation);
        void SetScale(glm::vec3 scale);
        void SetScale(glm::vec2 scale);
        void SetScale(float scale);
        void SetUnits(util::units::UNITS units);
        void SetProjectionType(util::projection_types::PROJECTION_TYPES projection_type);
        
        void Initialize(EXP::RenderTarget *target);
        void MakeLike(EXP::Model *model);
        
        glm::vec3 GetPosition() const;
        glm::vec3 GetScale() const;
        glm::vec3 GetRotation() const;
        Shader* GetShader() const;
        Material* GetMaterial() const;
        util::units::UNITS GetUnits() const;
        util::projection_types::PROJECTION_TYPES GetProjectionType() const;
        
        glm::mat4 GetTransformationMatrix(const Rect<float> &screen) const;
        glm::vec3 get_units_position(const Rect<float> &screen) const;
        glm::vec3 get_units_scale(const Rect<float> &screen) const;
        
        void Draw(unsigned index);
    protected:
        std::atomic<EXP::Shader*> shader;
        std::atomic<EXP::Mesh*> mesh;
        std::atomic<EXP::Material*> material;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        std::atomic<util::units::UNITS> units;
        std::atomic<util::projection_types::PROJECTION_TYPES> projection_type;
        
        glm::mat4 get_transformation_matrix(const Rect<float> &screen) const;
    };
}

#endif /* Model_hpp */
