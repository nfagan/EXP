//
//  Model.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Model/Model.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

EXP::Model::Model(EXP::Mesh *mesh, EXP::Material *material) : EXP::GLResourcePrimitive()
{
    SetMesh(mesh);
    SetMaterial(material);
    SetPosition(glm::vec3(0.0f));
    SetRotation(glm::vec3(0.0f));
    SetScale(glm::vec3(1.0f));
    SetShader(nullptr);
    SetUnits(EXP::util::units::NORMALIZED);
    SetProjectionType(EXP::util::projection_types::ORTHOGRAPHIC);
}

void EXP::Model::Draw(unsigned index)
{
    if (!shader)
    {
        std::cout << "WARNING: Attempted to draw before assigning a shader!" << std::endl;
        return;
    }
    material.load()->Configure(shader);
    mesh.load()->Draw(index);
}

void EXP::Model::Initialize(EXP::RenderTarget* target)
{
    //
}

void EXP::Model::MakeLike(EXP::Model *model)
{
    SetShader(model->GetShader());
    SetMaterial(model->GetMaterial());
    SetPosition(model->GetPosition());
    SetRotation(model->GetRotation());
    SetScale(model->GetScale());
    SetUnits(model->GetUnits());
}

void EXP::Model::SetShader(EXP::Shader *shader)
{
    this->shader.store(shader);
}

void EXP::Model::SetMaterial(EXP::Material *material)
{
    this->material.store(material);
}

void EXP::Model::SetScale(glm::vec3 scale)
{
    this->scale = scale;
}

void EXP::Model::SetScale(glm::vec2 scale)
{
    SetScale(glm::vec3(scale, 1.0f));
}

void EXP::Model::SetScale(float scale)
{
    SetScale(glm::vec3(scale));
}

void EXP::Model::SetPosition(glm::vec3 position)
{
    this->position = position;
}

void EXP::Model::SetPosition(glm::vec2 position)
{
    SetPosition(glm::vec3(position, 1.0f));
}

void EXP::Model::SetRotation(glm::vec3 rotation)
{
    this->rotation = rotation;
}

void EXP::Model::SetRotation(glm::vec2 rotation)
{
    SetRotation(glm::vec3(rotation, 1.0f));
}

void EXP::Model::SetUnits(EXP::util::units::UNITS units)
{
    this->units.store(units);
}

void EXP::Model::SetProjectionType(util::projection_types::PROJECTION_TYPES projection_type)
{
    this->projection_type.store(projection_type);
}

void EXP::Model::SetMesh(EXP::Mesh *mesh)
{
    this->mesh.store(mesh);
}

EXP::util::units::UNITS EXP::Model::GetUnits() const
{
    return units.load();
}

EXP::util::projection_types::PROJECTION_TYPES EXP::Model::GetProjectionType() const
{
    return projection_type.load();
}

glm::vec3 EXP::Model::GetPosition() const
{
    return position;
}

glm::vec3 EXP::Model::GetScale() const
{
    return scale;
}

glm::vec3 EXP::Model::GetRotation() const
{
    return rotation;
}

EXP::Shader* EXP::Model::GetShader() const
{
    return shader.load();
}

EXP::Material* EXP::Model::GetMaterial() const
{
    return material.load();
}

glm::mat4 EXP::Model::GetTransformationMatrix(const EXP::Rect<float> &screen) const
{
    return get_transformation_matrix(screen);
}

glm::mat4 EXP::Model::get_transformation_matrix(const Rect<float> &screen) const
{
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, get_units_position(screen));
    transform = glm::rotate(transform, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    return glm::scale(transform, get_units_scale(screen));
}

glm::vec3 EXP::Model::get_units_scale(const Rect<float> &screen) const
{
    using namespace util::units;
    
    glm::vec3 local_scale = GetScale();
    if (units == NORMALIZED)
    {
        local_scale.x *= screen.get_width();
        local_scale.y *= screen.get_height();
    }
    return local_scale;
}

glm::vec3 EXP::Model::get_units_position(const Rect<float> &screen) const
{
    using namespace util::units;
    
    glm::vec3 pos = GetPosition();
    if (units == NORMALIZED || units == MIXED)
    {
        pos.x = (pos.x * screen.get_width()) + screen.get_left();
        pos.y = (pos.y * screen.get_height()) + screen.get_top();
    }
    return pos;
}
