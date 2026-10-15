#pragma once

#include <string>

namespace gep
{
    class file_loader
    {
    public:
        static auto load(const std::string& path) -> std::string;
    };
}