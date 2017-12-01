//
//  MaterialAttribute.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/30/17.
//

#include <EXPGL/Material/MaterialAttribute.hpp>

EXP::MaterialAttribute::MaterialAttribute()
{
    Set(0.0f);
}

EXP::MaterialAttribute::MaterialAttribute(glm::vec3 data)
{
    Set(data);
}
EXP::MaterialAttribute::MaterialAttribute(const Texture *data)
{
    Set(data);
}
EXP::MaterialAttribute::MaterialAttribute(float data)
{
    Set(data);
}

EXP::MaterialAttribute::MaterialAttribute(const MaterialAttribute &data)
{
    copy_from(data);
}

EXP::MaterialAttribute& EXP::MaterialAttribute::operator=(const MaterialAttribute& other)
{
    if (&other == this) return *this;
    copy_from(other);
    return *this;
}

void EXP::MaterialAttribute::Set(glm::vec3 data)
{
    data_lock.lock();
    attribute.tag = Attribute::VEC3;
    attribute.data.vec3_value = data;
    data_lock.unlock();
}
void EXP::MaterialAttribute::Set(const Texture *data)
{
    data_lock.lock();
    attribute.tag = Attribute::TEXTURE;
    attribute.data.tex_value = data;
    data_lock.unlock();
}
void EXP::MaterialAttribute::Set(float data)
{
    data_lock.lock();
    attribute.tag = Attribute::FLOAT;
    attribute.data.float_value = data;
    data_lock.unlock();
}

void EXP::MaterialAttribute::Configure(Shader *shader)
{
    data_lock.lock();
    name_lock.lock();
    switch (attribute.tag)
    {
        case Attribute::VEC3:
            shader->SetBool((name + "_use_texture").c_str(), false);
            shader->SetVec3((name + "_value_vec3").c_str(), attribute.data.vec3_value);
            break;
        case Attribute::TEXTURE:
            shader->SetBool((name + "_use_texture").c_str(), true);
            shader->SetInt((name + "_value_sampler2d").c_str(), attribute.data.tex_value->GetIndex());
            break;
        case Attribute::FLOAT:
            shader->SetBool((name + "_use_texture").c_str(), false);
            shader->SetFloat((name + "_value_float").c_str(), attribute.data.float_value);
            break;
        default:
            assert(false);
    }
    data_lock.unlock();
    name_lock.unlock();
}

void EXP::MaterialAttribute::set_name(std::string name)
{
    name_lock.lock();
    this->name = name;
    name_lock.unlock();
}

void EXP::MaterialAttribute::copy_from(const MaterialAttribute &other)
{
    switch (other.attribute.tag)
    {
        case Attribute::VEC3:
            Set(other.attribute.data.vec3_value);
            break;
        case Attribute::TEXTURE:
            Set(other.attribute.data.tex_value);
            break;
        case Attribute::FLOAT:
            Set(other.attribute.data.float_value);
            break;
        default:
            assert(false);
    }
    set_name(other.name);
}
