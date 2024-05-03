#pragma once

#include <iostream>
#include <algorithm>
#include <cpr/cpr.h>
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

using namespace rapidjson;

namespace Stuckfish
{
	// consider creating a C-style structure to hold games data and a vector of this structure in Logic.
	struct GamesData
	{
		std::string pgn;
		std::string timeClass;
		std::string gameResult;
		std::string whiteRating;
		std::string blackRating;
		std::string whiteUsername;
		std::string blackUsername;
	};

	class Logic
	{
	public:
		Logic() : _gamesData()
		{};

		bool IsChessDotComUser(const std::string& username);		
		void GamesPlayedWithinPeriod(const std::string& username, const std::string& year, const std::string& month);
		void GetInfosFromListOfGamesPlayed(const std::string& username, const Document& doc);
		
	private:
		std::vector<GamesData> _gamesData;
	};
}

