#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/fwd.hpp>

namespace gep::core
{
    class [[nodiscard]] transform
    {
    public:

        auto get_model_matrix() const noexcept -> glm::mat4
        {
            glm::mat4 model{ 1.0f };
            model = glm::translate(model, position);
            model *= glm::mat4_cast(rotation);
            model = glm::scale(model, scale);
            return model;
        }

        auto get_position() const noexcept -> const glm::vec3& { return position; }
        auto get_rotation() const noexcept -> const glm::quat& { return rotation; }
        auto get_scale() const noexcept -> const glm::vec3& { return scale; }

        auto set_position(const glm::vec3& value) noexcept -> void { position = value; }
        auto set_rotation(const glm::quat& value) noexcept -> void { rotation = glm::normalize(value); }
        auto set_scale(const glm::vec3& value) noexcept -> void { scale = value; }

    private:
        glm::vec3 position{ 0.0f };
        glm::quat rotation{ 1.0f, 0.0f, 0.0f, 0.0f };
        glm::vec3 scale{ 1.0f };
    };
}
