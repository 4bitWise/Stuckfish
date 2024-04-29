#include "Stuckfish.hpp"
#include "Exceptions.hpp"

namespace Stuckfish
{
	class UserInfosPage : public Page
	{
	public:
		UserInfosPage(Core& app, Logic& logic) : _app(app), Page(logic) {}
		void OnUpdate() override;
		void OnUIRender() override;
	
	private:
		Core&		_app;
		std::string _username = "";
		bool		_textChanged = false;
	};

}

