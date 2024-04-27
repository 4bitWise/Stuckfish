#include "Stuckfish.hpp"
#include "Exceptions.hpp"

namespace Stuckfish
{
	class UserCredentials : public Page
	{
	public:
		UserCredentials(Core& app = Core::Get()) : _app(app) {}
		void OnUIRender() override;
		void OnUpdate() override;
	
	private:
		std::string _username = "";
		bool _textChanged = false;

		Core& _app;
	};
}