#include <glad/gl.h>
#include "game.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_Log.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <iostream>
#include <SDL3/SDL_surface.h>
#include "input/input_system.hpp"
#include "SDL3_image/SDL_image.h"
#include "time/TimeManager.h"
#include <string>

auto gep::game::init() noexcept -> bool
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());

		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	handle = SDL_CreateWindow( "GEP", 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL );

	if (handle == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "SDL_CreateWindow failed: %s", SDL_GetError());

		return false;
	}

	gl_context = SDL_GL_CreateContext(handle);

	/*
	auto version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
	if (version == 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL_Context_error: %s", SDL_GetError());
		return false;
	}

	int32_t major, minor, profile;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);

	SDL_Log("OpenGL version: %i.%i - Profile: %i", major, minor, profile);
	SDL_Log("GLAD version: %i %i", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	glClearColor(58 / 255.f, 51 / 255.f, 51 / 255.f, 1.0f);

	image = IMG_Load("assets/awesomeface.png");

	if (image == nullptr)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load failed: %s", SDL_GetError());

		return false;
	}

	//
	if (!renderer.init())
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Failed to initialize Renderer2D"
		);
		return false;
	}
	//

	return true;
	*/

	if (gl_context == nullptr)
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_VIDEO,
			"SDL_GL_CreateContext failed: %s",
			SDL_GetError()
		);
		return false;
	}

	if (gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0)
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Failed to initialize GLAD"
		);
		return false;
	}

	glClearColor(58 / 255.0f, 51 / 255.0f, 51 / 255.0f, 1.0f);

	if (!renderer.init())
	{
		SDL_LogError(
			SDL_LOG_CATEGORY_APPLICATION,
			"Failed to initialize Renderer2D"
		);
		return false;
	}

	return true;
}

auto gep::game::run() -> void
{
	
	auto& input_system = gep::input::input_system::instance();

	bool is_running = true;

	float image_x = 0.0f;
	float image_y = 0.0f;
	auto speed = 500.0f;

	SDL_Surface* window_surface = SDL_GetWindowSurface(handle);

	if (window_surface != nullptr && image != nullptr)
	{
		image_x = (window_surface->w - image->w) / 2;
		image_y = (window_surface->h - image->h) / 2;
	}

	while (is_running)
	{
		gep::time::Time::Instance().Tick();
		float deltaTime = gep::time::Time::Instance().GetDeltaTime();

		input_system.Update();

		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				is_running = false;
			}

			if (event.type == SDL_EVENT_KEY_DOWN &&
				event.key.key == SDLK_ESCAPE)
			{
				is_running = false;
			}

			input_system.process_input(event);
		}
		/*
		
		window_surface = SDL_GetWindowSurface(handle);

		if (window_surface == nullptr || image == nullptr)
		{
			continue;
		}

		if (input_system.IsKeyPressed(SDLK_W))
		{
			image_y -= speed * deltaTime;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 215, 0, 64));
		}

		if (input_system.IsKeyPressed(SDLK_A))
		{
			image_x -= speed * deltaTime;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 11, 218, 81));
		}

		if (input_system.IsKeyPressed(SDLK_S))
		{
			image_y += speed * deltaTime;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 4, 55, 242));
		}

		if (input_system.IsKeyPressed(SDLK_D))
		{
			image_x += speed * deltaTime;

			SDL_FillSurfaceRect(SDL_GetWindowSurface(handle), nullptr,
				SDL_MapRGB(SDL_GetPixelFormatDetails(SDL_GetWindowSurface(handle)->format), nullptr, 255, 215, 0));
		}

		if (image_x < 0)
		{
			image_x = 0;
		}

		if (image_y < 0)
		{
			image_y = 0;
		}

		if (image_x + image->w > window_surface->w)
		{
			image_x = window_surface->w - image->w;
		}

		if (image_y + image->h > window_surface->h)
		{
			image_y = window_surface->h - image->h;
		}

		SDL_Rect position{image_x, image_y, image->w, image->h};

		//SDL_BlitSurface(image, nullptr, window_surface, &position);

		//SDL_UpdateWindowSurface(handle);



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const char* vertexShaderSource = "#version 460 core\n"
			"layout (location = 0) in vec2 in_Pos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(in_Pos.x, in_Pos.y, 0.0, 1.0);\n"
			"}\0";

		const char* fragShaderSource = "#version 460 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
				"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
			"}\0";

		//Create shader objects
		uint32_t vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//give shader objects their source code
		glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(vertexShader);

		int32_t status = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		if (status == 0)
		{
			int32_t log_length;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &log_length);
			std::string log = std::string((std::size_t)log_length, ' ');
			glGetShaderInfoLog(vertexShader, log_length, nullptr, &log[0]);
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Vertex shader compile failure: %s", log.c_str());
		}

		glShaderSource(fragmentShader, 1, &fragShaderSource, nullptr);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		if (status == 0)
		{
			int32_t log_length;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &log_length);
			std::string log = std::string((std::size_t)log_length, ' ');
			glGetShaderInfoLog(fragmentShader, log_length, nullptr, &log[0]);
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Fragment shader compile failure: %s", log.c_str());
		}

		// Shader program creation --> OpenGL object
		uint32_t shaderProgram = glCreateProgram(); // Allocate
		// Attach shader to the shader program
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		// Link shader program
		glLinkProgram(shaderProgram);
		status = 0;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		if (status== 0)
		{
			int32_t log_length;
			glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &log_length);
			std::string log = std::string((std::size_t)log_length, ' ');
			glGetShaderInfoLog(shaderProgram, log_length, nullptr, &log[0]);
			SDL_LogError(SDL_LOG_CATEGORY_GPU,
				"Shader program compile failure: %s", log.c_str());
		}

		glDeleteShader(vertexShader); // Deallocate
		glDeleteShader(fragmentShader); // Deallocate

		// Use Shader program
		glUseProgram(shaderProgram);

		//Triangle
		float vertices[] = {
			// x	y
			-0.5f, -0.5f, // vertex 0 // Bytes 8 // Stride 8 // Offset 0
			0.5f, -0.5f,  // vertex 1 // Bytes 8
			0.0f, 0.5f,   // vertex 2 // Bytes 8
		};

		uint32_t vao, vbo, element_buffer_object;
		// vertex array object --> larger state/state machine inside opengl
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// vertex buffer object --> takes vertex data
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		uint32_t element_component_count = 2;
		uint32_t element_size = element_component_count * sizeof(float);
		uint32_t vertex_count = sizeof(vertices) / element_size;
		glVertexAttribPointer(0, element_component_count, GL_FLOAT, GL_FALSE, element_size, (void*)0);
		glEnableVertexAttribArray(0);
		glDrawArrays(GL_TRIANGLES, 0, vertex_count);

		glBindVertexArray(0);
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(shaderProgram);
*/

		glClear(GL_COLOR_BUFFER_BIT);


		//
		renderer.draw();
		//

		SDL_GL_SwapWindow(handle);
	}
	
}

auto gep::game::shutdown() noexcept -> void
{
	if (gl_context != nullptr)
	{
		SDL_GL_DestroyContext(gl_context);
	}

	if (image != nullptr)
	{
		SDL_DestroySurface(image);
	}

	if (handle != nullptr)
	{
		SDL_DestroyWindow(handle);
	}

	renderer.shutdown();

	SDL_Quit();
}