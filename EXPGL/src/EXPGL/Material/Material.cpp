//
//  Material.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/5/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Material/Material.hpp>

EXP::Material::Material() : EXP::GLResourcePrimitive()
{
    SetAlbedo(glm::vec3(1.0f));
};

void EXP::Material::Configure(EXP::Shader *shader)
{
    MaterialAttribute albedo_local(GetAlbedo());
    albedo_local.Configure(shader);
}

void EXP::Material::SetAlbedo(EXP::MaterialAttribute albedo)
{
    albedo.set_name("albedo");
    this->albedo.Set(albedo);
}

const EXP::MaterialAttribute& EXP::Material::GetAlbedo() const
{
    return albedo.Get();
}
