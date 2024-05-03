#pragma once

#include <iostream>
#include <algorithm>
#include <cpr/cpr.h>
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

namespace Stuckfish
{
	// consider creating a structure to hold games data and a vector of this structure in Logic.

	class Logic
	{
	public:
		// method to check if username exists on Chess.com
		bool IsChessDotComUser(const std::string& username);
		// method to fetch all the games played by the "specified" user in the month.
		void GamesPlayedWithinPeriod(const std::string& username, const std::string& year, const std::string& month);
	private:
		std::string _whiteUsername = "";
		std::string _blackUsername = "";
		std::string _whiteRating = "";
		std::string _blackRating = "";
		std::string _gameFormat = "";
		std::string _pgn = "";
	};
}

