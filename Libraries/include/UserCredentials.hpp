#include "Stuckfish.hpp"

namespace Stuckfish
{
	class UserCredentials : public Page
	{
	public:
		UserCredentials(Core& app = Core::Get()) : _app(app) {}
		void OnUIRender() override;

	private:
		std::string _useraccount = "";
		bool _textChanged = false;
		Core& _app;
	};
}