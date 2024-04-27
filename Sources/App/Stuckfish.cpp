#include <Stuckfish.hpp>
#include <UserCredentials.hpp>

static Stuckfish::Core* current_instance = nullptr;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


namespace Stuckfish
{
	Core::Core(const WindowSpecs& win_specs)
	{
		Init();

		current_instance = this;
	}

	Core::~Core()
	{
		Quit();

		current_instance = nullptr;
	}

	void Core::Init()
	{
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
		{
			std::cerr << "Could not initalize GLFW!\n";
			return;
		}

		const char* glsl_version = "#version 330";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		_window = glfwCreateWindow(_specs.width, _specs.height, _specs.name.c_str(), nullptr, nullptr);
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
		ImFontAtlas* fontAtlas = io.Fonts;

		_robotoFontHeader = fontAtlas->AddFontFromMemoryTTF((void*)roboto_regular, sizeof(roboto_regular), 28.0f);
		if (!_robotoFontHeader) {
			std::cerr << "Failed to load header font!" << std::endl;
			return;
		}

		_robotoFontBody = fontAtlas->AddFontFromMemoryTTF((void*)roboto_regular, sizeof(roboto_regular), 20.0f);
		if (!_robotoFontBody) {
			std::cerr << "Failed to load body font!" << std::endl;
			return;
		}

		_robotoFontBodyMedium = fontAtlas->AddFontFromMemoryTTF((void*)roboto_medium, sizeof(roboto_medium), 20.0f);
		if (!_robotoFontBodyMedium) {
			std::cerr << "Failed to load body medium font!" << std::endl;
			return;
		}

		io.FontDefault = _robotoFontBody;

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
					//ImGui::ShowDemoWindow();

					/*if (show_another_window)
					{
						ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
						ImGui::Text("Hello from another window!");
						if (ImGui::Button("Close Me"))
							show_another_window = false;
						ImGui::End();
					}*/
					for (auto& page : _pageStack)
					{
						page->OnUIRender();
						if (page->_errorOccured)
							DisplayErrorPopup(page->_errorMessage.c_str());
					}
				}

				ImGui::Render();

				glViewport(0, 0, _specs.width, _specs.height);
				glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
				glClear(GL_COLOR_BUFFER_BIT);
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				glfwSwapBuffers(_window);
			}
	}

	void Core::Quit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	Core& Core::Get()
	{
		return *current_instance;
	}

	std::unique_ptr<Core> CreateApplication(int argc, char* argv[])
	{
		WindowSpecs specs;

		std::unique_ptr<Core> app = std::make_unique<Core>(specs);

		app->PushLayer<UserCredentials>();
		return app;
	}

	void Core::DisplayErrorPopup(const char *error_message)
	{
		// Calculate the position of the popup in the upper right corner
		ImVec2 popupPos(_specs.width - ImGui::GetWindowSize().x / 2.8, 0);

		ImGui::OpenPopup("Error Popup");
		ImGui::SetNextWindowPos(popupPos, ImGuiCond_Always); // Set position relative to top right corner
		if (ImGui::BeginPopup("Error Popup", ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
			// Set the text color to red for the error message

			ImGui::PushFont(_robotoFontBodyMedium);
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "An error occurred");
			ImGui::PopFont();
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::Text(error_message);

			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - 25);
			if (ImGui::Button("OK", ImVec2(50, 0))) {
				for (auto& page : _pageStack)
				{
					page->_errorOccured = false;
					page->_errorMessage.clear();
				}
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		// Close popup when clicking outside of it
		if (ImGui::IsMouseClicked(0) && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
			for (auto& page : _pageStack)
			{
				page->_errorOccured = false;
				page->_errorMessage.clear();
			}
			ImGui::CloseCurrentPopup();
		}
	}
}
