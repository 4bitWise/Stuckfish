#pragma once

#include "Logic.hpp"
#include <memory.h>

namespace Stuckfish
{
	class Core;
}

namespace Stuckfish
{
	const float confirmButtonSizeX = 200.0f;
	const float confirmButtonSizeY = 35.0f;
	const float popupConfirmButtonSizeX = 50.0f;
	const float popupConfirmButtonSizeY = 0.0f;

	const float roundingValue = 5.0f;

	const float inputFieldWidth = 400;

	enum class WindowTitle
	{
		USERINFO_PAGE,
		LOADING_PAGE,
		GAMESPLAYED_PAGE,
		ERROR_POPUP
	};

	enum class Buttons
	{
		CONFIRM,
		OK
	};

	enum class Errors
	{
		EMPTY_USERNAME,
		USERNAME_NOT_FOUND
	};

	inline const char* WindowTitlesToString(WindowTitle t) {
		switch (t) {
			case WindowTitle::USERINFO_PAGE:	return "User Info Page";
			case WindowTitle::LOADING_PAGE:		return "Loading Page";
			case WindowTitle::GAMESPLAYED_PAGE: return "Games Played Page";
			case WindowTitle::ERROR_POPUP:		return "Error Popup";
			default:							return "[Unknown Page]";
		}
	}

	inline const char* ButtonsToString(Buttons b) {
		switch (b) {
			case Buttons::CONFIRM:   return "Confirm";
			case Buttons::OK:		 return "OK";
			default:			     return "[Unknown Button]";
		}
	}

	inline const char* ErrorsToString(Errors e) {
		switch (e) {
			case Errors::EMPTY_USERNAME:   return "Empty username.";
			case Errors::USERNAME_NOT_FOUND: return "Cannot find the username on Chess.com";
			default:					   return "[Unknown Error]";
		}
	}

	struct UserData
	{
		UserData(const std::string& name = "") : username(name)
		{};

		std::string username;
	};

	class Page
	{
	public:
		//static Page& GetInstance(Core& app, Logic& logic);
		
		virtual ~Page() = default; // virtual destructor as the class will be inherited.
		virtual void OnUpdate() {};
		virtual void OnUIRender() {};
		virtual void OnAttach() {};
		virtual void OnDetach() {};

		/*Page(const Page&) = delete;
		void operator=(const Page&) = delete;

		Page(Page&&) noexcept = default;
		Page& operator=(Page&&) noexcept = default;

		std::string& GetUsername(void)
		{
			return _username;
		}*/

	public:
		bool _errorOccured = false;
		std::string _errorMessage = "";
	
	protected:
		//Page(Core& app, Logic& logic);
		//Core& _app;
		//Logic& _logic;

		//std::string _username = "";
	};
}