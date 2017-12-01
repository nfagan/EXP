//
//  Mesh.cpp
//  EXPGL
//
//  Created by Nick Fagan on 10/22/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#include <EXPGL/Mesh/Mesh.hpp>
#include <EXPUtil/assert/EXP_ASSERT.h>
#include <gl.h>
#include <assert.h>

EXP::Mesh::Mesh() : EXP::GLResourcePrimitive()
{
    //
}

EXP::Mesh::~Mesh()
{
    for (unsigned i = 0; i < n_vaos; ++i) {
        glDeleteVertexArrays(1, &vaos[i]);
    }
    delete[] vaos;
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void EXP::Mesh::SetTopology(EXP::Mesh::TOPOLOGY topology)
{
    this->topology = topology;
}

void EXP::Mesh::SetIndices(std::vector<unsigned int> indices)
{
    this->indices = indices;
}

void EXP::Mesh::AddVertex(EXP::Vertex vertex)
{
    if (vertices.size() > 0 && !vertex.sizes_match(vertices[0]))
    {
        throw std::runtime_error("Vertices must have consistent numbers of elements.");
    }
    vertices.push_back(vertex);
}

void EXP::Mesh::Initialize(EXP::RenderTarget *target)
{
    if (IsInitialized())
    {
        throw std::runtime_error("Mesh was already initialized.");
    }
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    n_vaos = target->Size();
    vaos = new unsigned[n_vaos];
    is_initialized = true;
}

void EXP::Mesh::Finalize(EXP::RenderTarget *target)
{
    if (!IsInitialized())
    {
        throw std::runtime_error("Mesh was not yet initialized.");
    }
    if (IsFinalized())
    {
        throw std::runtime_error("Mesh was already finalized.");
    }
    for (unsigned i = 0; i < n_vaos; ++i)
    {
        target->GetWindow(i)->MakeCurrent();
        create_vao(i);
    }
    n_fragments = vertices.size();
    is_finalized = true;
}

bool EXP::Mesh::IsInitialized() const
{
    return is_initialized;
}

bool EXP::Mesh::IsFinalized() const
{
    return is_finalized;
}

void EXP::Mesh::Bind(unsigned index) const
{
    glBindVertexArray(vaos[index]);
}

void EXP::Mesh::Unbind() const
{
    glBindVertexArray(0);
}

void EXP::Mesh::Draw(unsigned index) const
{
    Bind(index);
    switch (topology) {
        case TRIANGLES:
            if (indices.size() > 0)
            {
                glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_TRIANGLES, 0, n_fragments);
            }
            break;
        case TRIANGLE_STRIP:
            if (indices.size() > 0)
            {
                glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
            }
            else
            {
                glDrawArrays(GL_TRIANGLE_STRIP, 0, n_fragments);
            }
            break;
        default:
            //  Not yet implemented
            assert(false);
            break;
    }
    Unbind();
}

void EXP::Mesh::create_vao(unsigned int index)
{
    if (vertices.size() == 0)
    {
        return;
    }
    
    std::vector<float> vertex_data = get_interleaved_data();
    
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    unsigned n_vertex_elements = vertex_data.size();
    GLsizei stride = sizeof(float) * vertices[0].size();
    unsigned offset = 0;
    
    //  store vertices in VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n_vertex_elements, &vertex_data[0], GL_STATIC_DRAW);
    
    //  position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(0);
    offset += 3;
    
    //  tex coords
    if (vertices[0].size_uv() > 0)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(offset*sizeof(float)));
        glEnableVertexAttribArray(1);
        offset += 2;
    }
    
    //  normals
    if (vertices[0].size_normal() > 0)
    {
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(offset*sizeof(float)));
        glEnableVertexAttribArray(2);
        offset += 3;
    }
    
    //  indices
    if (indices.size() > 0)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
    }
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    vaos[index] = vao;
}

std::vector<float> EXP::Mesh::get_interleaved_data() const
{
    std::vector<float> vertex_data;
    for (unsigned i = 0; i < vertices.size(); ++i)
    {
        std::vector<float> data = vertices[i].get_interleaved_data();
        for (unsigned j = 0; j < data.size(); ++j)
        {
            vertex_data.push_back(data[j]);
        }
    }
    return vertex_data;
}
