#include "../Libraries/include/Stuckfish.hpp"

int main(int argc, char* argv[])
{
	std::unique_ptr<Stuckfish::Core> app = Stuckfish::CreateApplication();
	
	app->Run();
	app.release();

	return 0;
}