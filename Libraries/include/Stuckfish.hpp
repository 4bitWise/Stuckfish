#pragma once

#include <string>
#include <memory>
#include <stdio.h>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_stdlib.h>

#include "fonts.hpp"
#include "Page.hpp"

#include <vector>

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
		uint32_t width = 1500;
		uint32_t height = 800;
	};

	class Core
	{
	public:
		Core(const WindowSpecs& win_specs = WindowSpecs());
		~Core();

		void Run();
		
		static Core& Get();
		
		template<typename T>
		void PushLayer() {
			static_assert(std::is_base_of<Page, T>::value, "Pushed type is not subclass of Page!");
			_pageStack.emplace_back(std::make_shared<T>());
		}

		void DisplayErrorPopup(const char *error_message);

	public:
		bool _isRunning = true;

		ImFont* _robotoFontHeader = nullptr;
		ImFont* _robotoFontBody = nullptr;
		ImFont* _robotoFontBodyMedium = nullptr;

		WindowSpecs _specs;
	private:
		void Init();
		void Quit();

	private:
		GLFWwindow* _window = nullptr;

		std::vector<std::shared_ptr<Page>> _pageStack;
	};

	std::unique_ptr<Core> CreateApplication(int argc, char* argv[]);
};