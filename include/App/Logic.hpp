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
		int statusCode;
		std::string message;
		std::vector<GamesData> gamesData;
	};

	enum ResponseCode
	{
		OK = 0,
		NO_GAMES_FOUND,
		DATA_EXTRACTION_ERROR,
		MISSING_FIELD_ERROR,
		PARSING_ERROR,
		NETWORK_ERROR
	};

	struct UserData
	{
		UserData(const std::string& name = "") : username(name)
		{};

		std::string username;
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

// class to fetch the games data will be named differently
