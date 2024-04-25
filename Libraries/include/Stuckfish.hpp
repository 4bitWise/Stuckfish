#pragma once

#include <string>
#include <memory>
#include <stdio.h>
#include <iostream>
#include <fonts.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h> // Will drag system OpenGL headers


#ifdef __EMSCRIPTEN__
	#include "../emscripten/emscripten_mainloop_stub.h"
#endif

namespace Stuckfish
{
	struct WindowSpecs
	{
		std::string name = "Stuckfish";
		uint32_t width = 1600;
		uint32_t height = 900;
	};

	class Core
	{

	public:
		Core(const WindowSpecs& win_specs = WindowSpecs());
		~Core();

		void Run();

		bool _isRunning = true;

	private:
		void Init();
		void Quit();

	private:
		GLFWwindow* _window = nullptr;
	};

	std::unique_ptr<Core> CreateApplication(int argc, char* argv[]);
};