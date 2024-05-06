/******************************************************************************
 * File:        Main.cpp
 * Authors:     see AUTHORS file
 *****************************************************************************/

#include "../include/App/Stuckfish.hpp"

int main(int argc, char* argv[])
{
	Stuckfish::WindowSpecs specs;
	std::unique_ptr<Stuckfish::Core> app = std::make_unique<Stuckfish::Core>(specs);

	app->Run();
	app.release();

	return 0;
}