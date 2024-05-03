/******************************************************************************
 * File:        UserInfosPage.hpp
 * Authors:     see AUTHORS file
 * Date:        May 3, 2024
 * Description: This file contains the required methods to render the 1st page
 *****************************************************************************/

#include "Page.hpp"
#include "Exceptions.hpp"

namespace Stuckfish
{
	class UserInfosPage : public Page
	{
	public:
		UserInfosPage(Core& app, Logic& logic, UserData& userData) : _app(app), _logic(logic), _userdata(userData)
		{}

		void OnUpdate() override;
		void OnUIRender() override;
		void OnAttach() override;
		void OnDetach() override;

	private:
		Core& _app;
		Logic& _logic;
		UserData& _userdata;
	};
}

