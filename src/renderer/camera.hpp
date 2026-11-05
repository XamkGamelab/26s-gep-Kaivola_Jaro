#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../core/transform.hpp"

namespace gep::renderer
{
	class [[nodiscard]] camera
	{
	public:

		camera(float width, float height, float size = 5.0f)
			: width(width), height(height), size(size)
		{
			resolve_projection_matrix();
		}

		auto get_projection_matrix() const noexcept -> const glm::mat4& { return projection_matrix; }
		auto get_view_matrix() const noexcept -> glm::mat4
		{
			return glm::inverse(camera_transform.get_model_matrix());
		}

		auto get_position() const noexcept -> glm::vec3 { return camera_transform.get_position(); }
		auto set_position(const glm::vec3& value) noexcept -> void { camera_transform.set_position(value); }

		auto get_transform() noexcept -> core::transform& { return camera_transform; }
		auto get_transform() const noexcept -> const core::transform& { return camera_transform; }


		auto resize(float new_width, float new_height) noexcept -> void
		{
			if (new_width <= 0.0f || new_height <= 0.0f) return;
			width = new_width;
			height = new_height;
			resolve_projection_matrix();
		}


	private:

		float width{ 1280.0f }, height{ 720.0f }, size{ 5.0f };
		core::transform camera_transform{};

		glm::mat4 projection_matrix{ 1.0f };

		auto resolve_projection_matrix() noexcept -> void
		{
			const float half_height = size;
			const float half_width = half_height * (width / height);
			projection_matrix = glm::ortho(-half_width, half_width,
				-half_height, half_height, -1.0f, 1.0f);
		}

	};
}