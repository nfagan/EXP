//
//  GLResourceManager.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/30/17.
//

#include <stdio.h>
#include <EXPGL/Loaders/GLResourceManager.hpp>

EXP::GLResourceManager::GLResourceManager(EXP::RenderTarget *target) : target(target)
{
    texture_loader = std::make_unique<TextureLoader>();
    n_items = 0;
}

EXP::GLResourceManager::~GLResourceManager()
{
    for (unsigned i = 0; i < items.size(); ++i)
    {
        delete items[i];
    }
}

EXP::Model* EXP::GLResourceManager::make_model(Mesh *mesh)
{
    mesh->Finalize(target);
    Material *mat = Create<Material>();
    Model *model = Create<Model>(mesh, mat);
    return model;
}

EXP::Shader* EXP::GLResourceManager::CreateGenericShader()
{
    Shader* shader = Create<Shader>();
    ShaderLibrary::make_generic(shader);
    return shader;
}

EXP::Model* EXP::GLResourceManager::CreateRectangle()
{
    Mesh *mesh = Create<Mesh>();
    MeshLibrary::make_quad(mesh);
    return make_model(mesh);
}

EXP::Model* EXP::GLResourceManager::CreateSphere(int vertex_count)
{
    Mesh *mesh = Create<Mesh>();
    MeshLibrary::make_sphere(mesh, vertex_count);
    return make_model(mesh);
}

EXP::Model* EXP::GLResourceManager::CreateTriangle()
{
    Mesh *mesh = Create<Mesh>();
    MeshLibrary::make_triangle(mesh);
    return make_model(mesh);
}

void EXP::GLResourceManager::SetName(GLResourcePrimitive *resource, const std::string &name)
{
    for (unsigned i = 0; i < items.size(); ++i)
    {
        if (items[i]->GetIdentifier().GetName() == name)
        {
            throw std::runtime_error("An item with the name `" + name + "` already exists.");
        }
    }
    
    std::string current_name = resource->GetIdentifier().GetName();
    auto it = indices.find(current_name);
    if (it == indices.end())
    {
        throw std::logic_error("The name `" + current_name + "` was not present??");
    }
    unsigned index = it->second;
    indices.erase(it);
    indices[name] = index;
}
