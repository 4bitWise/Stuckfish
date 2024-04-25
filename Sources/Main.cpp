#include <Stuckfish.hpp>

int main(int argc, char* argv[])
{
	std::unique_ptr<Stuckfish::Core> app = Stuckfish::CreateApplication(argc, argv);
	
	while (app->_isRunning)
	{
		app->Run();
	}
	return 0;
}