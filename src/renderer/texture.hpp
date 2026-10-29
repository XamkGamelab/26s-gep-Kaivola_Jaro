#pragma once
#include <cstdint>
#include <string_view>

namespace gep::renderer
{
	class [[nodiscard]] Texture
	{
	public:
		Texture() = default;
		Texture(std::string_view path);
		~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;

		auto bind() const noexcept -> void;
		auto width() const noexcept -> int { return w; }
		auto height() const noexcept -> int { return h; }

	private:
		uint32_t id{ 0 };
		int w{ 0 }, h{ 0 };
	};
}
