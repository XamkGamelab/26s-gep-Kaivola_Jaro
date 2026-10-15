#pragma once

#include <glad/gl.h>
#include <string>

namespace gep
{
    class Shader
    {
    public:
        auto init(
            const std::string& vertexPath,
            const std::string& fragmentPath
        ) -> bool;

        auto use() const -> void;
        auto shutdown() -> void;

        ~Shader();

        Shader() = default;
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

    private:
        unsigned int shaderProgram = 0;
    };
}