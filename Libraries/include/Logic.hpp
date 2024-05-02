#pragma once

#include <iostream>
#include <algorithm>
#include <cpr/cpr.h>

namespace Stuckfish
{

	enum HttpStatusCode
	{
		SUCCESS = 200,
		UNAUTHORIZED = 401,
	};

	class Logic
	{
	public:
		// method to check if username exists on Chess.com
		bool IsChessComUser(const std::string& username);
		// method to fetch all the games played by the "specified" user in the month.
		void GamesPlayedWithinPeriod(const std::string& username, const std::string& year, const std::string& month);
	private:
	};
}

