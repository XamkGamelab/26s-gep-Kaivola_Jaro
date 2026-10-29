#pragma once
#include <string_view>
#include <cstdint>

namespace gep::renderer
{
	class [[nodiscard]] shader
	{
	public:
		shader() = default;
		~shader();
		shader(std::string_view v_path, std::string_view f_path);

		auto get_id() const noexcept -> uint32_t { return id; }
		auto bind() const noexcept -> void;
		auto clear() -> void;

		auto set_integer(std::string_view name, int value) const -> void;
		auto set_matrix(std::string_view name, const float* matrix) const -> void;


		shader(const shader&) = delete;
		shader& operator=(const shader&) = delete;

		shader(shader&& rhs) noexcept;
		shader& operator=(shader&& rhs) noexcept;

	private:
		uint32_t id{ 0 };

		auto compile_shader(uint32_t shader, const char* source) const -> bool;
	};
}