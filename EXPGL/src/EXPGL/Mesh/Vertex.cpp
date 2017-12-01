//
//  Vertex.cpp
//  EXPGL
//
//  Created by Nick Fagan on 11/30/17.
//

#include <EXPGL/Mesh/Vertex.hpp>

void EXP::Vertex::set_position(std::array<float, 3> in_position)
{
    position = in_position;
    n_position = 3;
}

void EXP::Vertex::set_uv(std::array<float, 2> in_uv)
{
    uv = in_uv;
    n_uv = 2;
}

void EXP::Vertex::set_normal(std::array<float, 3> in_normal)
{
    normal = in_normal;
    n_normal = 3;
}

unsigned int EXP::Vertex::size() const
{
    return n_position + n_uv + n_normal;
}

unsigned int EXP::Vertex::size_position() const
{
    return n_position;
}

unsigned int EXP::Vertex::size_uv() const
{
    return n_uv;
}

unsigned int EXP::Vertex::size_normal() const
{
    return n_normal;
}

bool EXP::Vertex::sizes_match(const Vertex &other) const
{
    return n_position == other.n_position && n_uv == other.n_uv && n_normal == other.n_normal;
}

std::vector<float> EXP::Vertex::get_interleaved_data() const
{
    std::vector<float> data;
    for (unsigned i = 0; i < n_position; ++i)
    {
        data.push_back(position[i]);
    }
    for (unsigned i = 0; i < n_uv; ++i)
    {
        data.push_back(uv[i]);
    }
    for (unsigned i = 0; i < n_normal; ++i)
    {
        data.push_back(normal[i]);
    }
    return data;
}
