#pragma once

#include "Shader.hpp"

namespace gep
{
    class Renderer2D
    {
    public:
        auto init() -> bool;
        auto draw() -> void;
        auto shutdown() -> void;

        ~Renderer2D();

        Renderer2D() = default;
        Renderer2D(const Renderer2D&) = delete;
        Renderer2D& operator=(const Renderer2D&) = delete;

    private:
        Shader shader;
        unsigned int vao = 0;
        unsigned int vbo = 0;
        unsigned int ebo = 0;
    };
}