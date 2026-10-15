#include "file_loader.hpp"
#include <fstream>
#include <sstream>

auto gep::file_loader::load(const std::string& path) -> std::string
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}