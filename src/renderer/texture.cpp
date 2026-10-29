#include "texture.hpp"
#include <glad/gl.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_error.h>
#include <string>
#include <utility>

namespace gep::renderer
{
	Texture::Texture(std::string_view path)
	{
		const std::string filename(path);
		auto* image = IMG_Load(filename.c_str());
		if (!image)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Image '%s' failed to load: %s", filename.c_str(), SDL_GetError());
			return;
		}

		auto* rgba = SDL_ConvertSurface(image, SDL_PIXELFORMAT_RGBA32);
		SDL_DestroySurface(image);
		if (!rgba)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Image '%s' conversion failed: %s", filename.c_str(), SDL_GetError());
			return;
		}

		if (!SDL_FlipSurface(rgba, SDL_FLIP_VERTICAL))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Image '%s' flip failed: %s", filename.c_str(), SDL_GetError());
			SDL_DestroySurface(rgba);
			return;
		}

		w = rgba->w;
		h = rgba->h;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLint old_alignment, old_row_length;
		glGetIntegerv(GL_UNPACK_ALIGNMENT, &old_alignment);
		glGetIntegerv(GL_UNPACK_ROW_LENGTH, &old_row_length);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, rgba->pitch / 4);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, old_row_length);
		glPixelStorei(GL_UNPACK_ALIGNMENT, old_alignment);
		SDL_DestroySurface(rgba);
	}

	Texture::~Texture()
	{
		if (id) glDeleteTextures(1, &id);
	}

	Texture::Texture(Texture&& other) noexcept
		: id(std::exchange(other.id, 0)), w(std::exchange(other.w, 0)), h(std::exchange(other.h, 0)) {}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		if (this != &other)
		{
			if (id) glDeleteTextures(1, &id);
			id = std::exchange(other.id, 0);
			w = std::exchange(other.w, 0);
			h = std::exchange(other.h, 0);
		}
		return *this;
	}

	auto Texture::bind() const noexcept -> void
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
}
