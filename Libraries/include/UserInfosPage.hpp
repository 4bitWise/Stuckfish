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

