/******************************************************************************
 * File:        Stuckfish.hpp
 * Authors:     see AUTHORS file
 * Date:        May 3, 2024
 * Description: This file contains the Core class and setup methods
 *****************************************************************************/

#pragma once

#include <string>
#include <memory>
#include <stdio.h>
#include <iostream>

#include "../Imgui.hpp"

#include "../UI/fonts.hpp"
#include "../UI/Page.hpp"
#include "../UI/HomePage.hpp"

#include <vector>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h> // Will drag system OpenGL headers


#ifdef __EMSCRIPTEN__
	#include "../emscripten/emscripten_mainloop_stub.h"
#endif

#define GLSL_VERSION "#version 330"


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

		void Run(void);
		void DisplayErrorPopup(const char *error_message);
		void RemoveErrorPopup(void);

	public:
		ImFont* robotoFontHeader = nullptr;
		ImFont* robotoFontBody = nullptr;
		ImFont* robotoFontBodyMedium = nullptr;

		WindowSpecs specs;
		Logic logic;
		bool  errorOccured = false;
		std::string errorMessage;
	private:
		void Init(void);
		void Quit(void);

	private:
		GLFWwindow* _window = nullptr;
		HomePage    _homePage;
	};
};