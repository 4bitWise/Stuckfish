#include "../../Libraries/include/Stuckfish.hpp"
#include "../../Libraries/include/UserInfosPage.hpp"
#include "../../Libraries/include/GamesPlayedPage.hpp"

static Stuckfish::Core* current_instance = nullptr;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

template<typename T>
T* check_return(T* ptr, const char* error_msg) {
	if (!ptr)
	{
		std::cerr << error_msg << std::endl;
		exit(1);
	}
	return ptr;
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

	void Core::Init(void)
	{
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
		{
			std::cerr << "Could not initalize GLFW!\n";
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		_window = check_return(glfwCreateWindow(_specs.width, _specs.height, _specs.name.c_str(), nullptr, nullptr), "Unable to create window. Exiting with code 1.");
		glfwMakeContextCurrent(_window);
		glfwSwapInterval(1); // Enable vsync

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		ImGui::StyleColorsDark();								  // Setup Dear ImGui style

		// Load Fonts
		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = true;
		ImFontAtlas* fontAtlas = io.Fonts;
		_robotoFontHeader = check_return(fontAtlas->AddFontFromMemoryTTF((void*)roboto_regular, sizeof(roboto_regular), 28.0f), "Failed to load roboto header regular font.");
		_robotoFontBody = check_return(fontAtlas->AddFontFromMemoryTTF((void*)roboto_regular, sizeof(roboto_regular), 20.0f), "Failed to load roboto body regular font!");
		_robotoFontBodyMedium = check_return(fontAtlas->AddFontFromMemoryTTF((void*)roboto_medium, sizeof(roboto_medium), 20.0f), "Failed to load roboto body medium font!");
		io.FontDefault = _robotoFontBody;

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init(GLSL_VERSION);
	}

	void Core::Run(void)
	{
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
					
					_pageStack.front()->OnUIRender();
					if (_pageStack.front()->_errorOccured)
						DisplayErrorPopup(_pageStack.front()->_errorMessage.c_str());
				}

				ImGui::Render();

				glViewport(0, 0, _specs.width, _specs.height);
				glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
				glClear(GL_COLOR_BUFFER_BIT);
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
				glfwSwapBuffers(_window);
			}
	}

	void Core::Quit(void)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// Clear page stack
		_pageStack.clear();

		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	Core& Core::Get(void)
	{
		return *current_instance;
	}

	std::unique_ptr<Core> CreateApplication(int argc, char* argv[])
	{
		WindowSpecs specs;

		std::unique_ptr<Core> app = std::make_unique<Core>(specs);
		//Page& page = Page::GetInstance(Core::Get(), appLogic);

		app->PushLayer<UserInfosPage>(Core::Get(), app->_appLogic, app->_userData);
		app->PushLayer<GamesPlayedPage>(Core::Get(), app->_appLogic, app->_userData);
		
		return app;
	}

	void Core::DisplayErrorPopup(const char *error_message)
	{
		// Calculate the position of the popup in the upper right corner
		ImVec2 popupPos(static_cast<float>(_specs.width - ImGui::GetWindowSize().x / 2.8), 0);
		ImVec4 redColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

		ImGui::OpenPopup(WindowTitlesToString(WindowTitle::ERROR_POPUP));
		ImGui::SetNextWindowPos(popupPos, ImGuiCond_Always); // Set position relative to top right corner
		if (ImGui::BeginPopup(WindowTitlesToString(WindowTitle::ERROR_POPUP),
			ImGuiWindowFlags_AlwaysAutoResize | 
			ImGuiWindowFlags_NoMove))
		{
	
			ImGui::PushFont(_robotoFontBodyMedium);
			ImGui::TextColored(redColor, "An error occurred");
			ImGui::PopFont();
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::TextWrapped(error_message);

			ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - 25);
			if (ImGui::Button("OK", ImVec2(popupConfirmButtonSizeX, popupConfirmButtonSizeY)))
				RemoveErrorPopup();
			ImGui::EndPopup();
		}

		// Close popup when clicking outside of it
		if (ImGui::IsMouseClicked(0) && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
			RemoveErrorPopup();
	}

	void Core::RemoveErrorPopup(void)
	{
		for (auto& page : _pageStack)
		{
			page->_errorOccured = false;
			page->_errorMessage.clear();
		}
		ImGui::CloseCurrentPopup();
	}
}
