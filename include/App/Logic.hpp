/******************************************************************************
 * File:        Logic.hpp
 * Authors:     see AUTHORS file
 * Date:        May 3, 2024
 * Description: This file contains the API requests methods
 *****************************************************************************/

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
		std::string result;
		std::string whiteRating;
		std::string blackRating;
		std::string whiteUsername;
		std::string blackUsername;
	};

	struct Response
	{
		int errorCode;
		std::string errorMessage;
		std::vector<GamesData> gamesData;
	};

	class Logic
	{
	public:
		Logic() : _gamesData(), _res()
		{};

		bool IsChessDotComUser(const std::string& username);		
		const Response& GamesPlayedWithinPeriod(const std::string& username, const std::string& year, const std::string& month);
		void GetInfosFromListOfGamesPlayed(const std::string& username, const Document& doc);
		
	private:
		std::vector<GamesData> _gamesData;
		Response			   _res;
	};
}

