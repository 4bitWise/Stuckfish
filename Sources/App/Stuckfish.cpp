#include <Stuckfish.hpp>


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

namespace Stuckfish
{
	Core::Core(const WindowSpecs& win_specs)
	{
		Init();
	}

	Core::~Core()
	{}

	void Core::Init()
	{
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
		{
			std::cerr << "Could not initalize GLFW!\n";
			return;
		}

		// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
		const char* glsl_version = "#version 100";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 330";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

		_window = glfwCreateWindow(1920, 1080, "Stuckfish global interface", nullptr, nullptr);
		if (_window == nullptr)
			return;

		glfwMakeContextCurrent(_window);
		glfwSwapInterval(1); // Enable vsync

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();


		// Load Fonts
		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = true;
		ImFont* robotoFont = io.Fonts->AddFontFromMemoryTTF((void*)roboto_regular, sizeof(roboto_regular), 18.0f);
		io.FontDefault = robotoFont;

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void Core::Run()
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		bool show_another_window = true;

		#ifdef __EMSCRIPTEN__
			io.IniFilename = nullptr;
			EMSCRIPTEN_MAINLOOP_BEGIN
		#else
			while (!glfwWindowShouldClose(_window))
		#endif
			{
				glfwPollEvents();

				// Start the Dear ImGui frame
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();


				{
					ImGui::ShowDemoWindow();
					if (show_another_window)
					{
						ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
						ImGui::Text("Hello from another window!");
						if (ImGui::Button("Close Me"))
							show_another_window = false;
						ImGui::End();
					}
				}
				ImGui::Render();

				glViewport(0, 0, 1920, 1080);
				glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
				glClear(GL_COLOR_BUFFER_BIT);
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				glfwSwapBuffers(_window);
			};
			Quit();
	}

	void Core::Quit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(_window);
		glfwTerminate();
		
		_isRunning = false;
	}

	std::unique_ptr<Core> CreateApplication(int argc, char* argv[])
	{
		WindowSpecs specs;
		return std::make_unique<Core>(specs);
	}
}
