#include "Shader.hpp"
#include "../file_loader.hpp"

#include <SDL3/SDL_log.h>
#include <string>
#include <exception>

auto gep::Shader::init(const std::string& vertexPath, const std::string& fragmentPath) -> bool
{
    std::string vertexSource;
    std::string fragmentSource;

    try
    {
        vertexSource = file_loader::load(vertexPath);
        fragmentSource = file_loader::load(fragmentPath);
    }
    catch (const std::exception& e)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", e.what());
        return false;
    }

    auto compileShader = [](GLenum type, const std::string& source) -> unsigned int
        {
            unsigned int shader = glCreateShader(type);
            const char* code = source.c_str();

            glShaderSource(shader, 1, &code, nullptr);
            glCompileShader(shader);

            int success = GL_FALSE;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                int length = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

                std::string log(static_cast<std::size_t>(length), '\0');
                glGetShaderInfoLog(shader, length, nullptr, log.data());

                SDL_LogError(
                    SDL_LOG_CATEGORY_APPLICATION,
                    "Shader compilation failed: %s",
                    log.c_str()
                );

                glDeleteShader(shader);
                return 0;
            }

            return shader;
        };

    unsigned int vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
    if (vertex == 0)
        return false;

    unsigned int fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragment == 0)
    {
        glDeleteShader(vertex);
        return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertex);
    glAttachShader(shaderProgram, fragment);
    glLinkProgram(shaderProgram);

    int success = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    if (!success)
    {
        int length = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);

        std::string log(static_cast<std::size_t>(length), '\0');
        glGetProgramInfoLog(shaderProgram, length, nullptr, log.data());

        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Shader linking failed: %s", log.c_str());

        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
        return false;
    }

    return true;
}

auto gep::Shader::use() const -> void
{
    glUseProgram(shaderProgram);
}

auto gep::Shader::shutdown() -> void
{
    if (shaderProgram != 0)
    {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
}

gep::Shader::~Shader()
{
    shutdown();
}