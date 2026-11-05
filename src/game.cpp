#include <glad/gl.h>
#include "game.hpp"

#include <string>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_mouse.h>

#include <SDL3_image/SDL_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "input/input_system.hpp"
#include "renderer/renderer2D.hpp"
#include "renderer/texture.hpp"

#include "core/transform.hpp"
#include "renderer/camera.hpp"
#include "time/TimeManager.h"

auto gep::game::init() noexcept -> bool
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
			"SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window_handle = SDL_CreateWindow("Gep", 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (window_handle == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO,
			"SDL_CreateWindow failed: %s", SDL_GetError());
		return false;
	}

	gl_context = SDL_GL_CreateContext(window_handle);
	auto version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
	if (version == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM,
			"SDL_GL_CreateContext failed: %s", SDL_GetError());
		return false;
	}

	int32_t major, minor, profile;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);

	SDL_Log("OpenGL version: %i.%i - Profile: %i", major, minor, profile);
	SDL_Log("GLAD version: %i.%i", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	glEnable(GL_BLEND);
	glClearColor(58 / 255.f, 51 / 255.f, 51 / 255.f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

auto gep::game::run() -> void
{
	int32_t window_width;
	int32_t window_height;
	SDL_GetWindowSize(window_handle, &window_width, &window_height);

	auto& input_system = input::input_system::instance();
	renderer::renderer_2d renderer{};

	glViewport(0, 0, window_width, window_height);

	core::transform transform0{};
	transform0.set_position({ -3.0f, 0.0f, 0.0f });

	core::transform transform1{};
	transform1.set_position({ 0.0f, 1.0f, 0.0f });
	transform1.set_rotation(glm::angleAxis(glm::radians(45.0f), glm::vec3{ 0.0f, 0.0f, 1.0f }));

	core::transform transform2{};
	transform2.set_position({ 3.0f, -1.0f, 0.0f });
	transform2.set_scale({ 5.0f, 2.5f, 1.0f });
	transform2.set_rotation(glm::angleAxis(glm::radians(90.0f), glm::vec3{ 0.0f, 0.0f, 1.0f }));

	renderer::camera camera{ static_cast<float>(window_width), static_cast<float>(window_height), 5.0f };

	renderer::texture tex{ "assets/awesomeface.png" };
	float camera_speed = 5.0f;
	auto& time_manager = time::Time::Instance();
	float rotation_time = 0.0f;

	bool is_running = true;
	while (is_running)
	{

		time_manager.Tick();
		const float delta_time = time_manager.GetDeltaTime();
		input_system.update();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				is_running = false;
				return;
			}

			if (event.type == SDL_EVENT_WINDOW_RESIZED)
			{
				SDL_GetWindowSize(window_handle, &window_width, &window_height);
				SDL_Log("Window resized: %i %i", window_width, window_height);
				camera.resize(static_cast<float>(window_width), static_cast<float>(window_height));
				glViewport(0, 0, window_width, window_height);
			}

			input_system.process_input(event);
		}

		rotation_time += delta_time;
		transform1.set_rotation(glm::angleAxis(rotation_time, glm::vec3{ 0.0f, 0.0f, 1.0f }));

		glm::vec3 camera_direction{ 0.0f };
		if (input_system.is_key_pressed(SDLK_W))
			camera_direction.y += 1.0f;
		if (input_system.is_key_pressed(SDLK_S))
			camera_direction.y -= 1.0f;
		if (input_system.is_key_pressed(SDLK_A))
			camera_direction.x -= 1.0f;
		if (input_system.is_key_pressed(SDLK_D))
			camera_direction.x += 1.0f;

		if (glm::length(camera_direction) > 0.0f)
		{
			camera_direction = glm::normalize(camera_direction);
			camera.set_position(camera.get_position() + camera_direction * camera_speed * delta_time);
		}

		renderer.clear();
		renderer.draw_quad(transform0, tex, camera);
		renderer.draw_quad(transform1, tex, camera);
		renderer.draw_quad(transform2, tex, camera);
		SDL_GL_SwapWindow(window_handle);
	}
}

auto gep::game::shutdown() noexcept -> void
{
	if (gl_context != nullptr)
	{
		SDL_GL_DestroyContext(gl_context);
	}

	if (window_handle != nullptr)
	{
		SDL_DestroyWindow(window_handle);
	}

	SDL_Quit();
}