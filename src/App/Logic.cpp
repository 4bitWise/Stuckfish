/******************************************************************************
 * File:        Logic.cpp
 * Authors:     see AUTHORS file
 *****************************************************************************/

#include "../../include/App/Logic.hpp"

static std::string
to_lower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](char c)
        { return std::tolower(c); });
    return s;
}

static std::string
extractString(const Value& jsonObject, const std::string& fieldName)
{
    if (jsonObject.HasMember(fieldName.c_str()) && jsonObject[fieldName.c_str()].IsString())
        return jsonObject[fieldName.c_str()].GetString();
    return "";
}

static std::string
extractInt(const Value& jsonObject, const std::string& fieldName)
{
    if (jsonObject.HasMember(fieldName.c_str()) && jsonObject[fieldName.c_str()].IsInt())
        return std::to_string(jsonObject[fieldName.c_str()].GetInt());
    return "";
}

namespace Stuckfish
{

//------------------------------------------------------------------------------
/**
*/
bool
Logic::IsChessDotComUser(const std::string& username)
{
    std::string url = "https://api.chess.com/pub/player/" + to_lower(username);
    cpr::Response res = cpr::Get(cpr::Url{ url });

    if (res.status_code == cpr::status::HTTP_OK)
        return true;
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
Logic::GetInfosFromListOfGamesPlayed(const std::string& username, const Document& doc)
{
    // Check if parsing succeeded
    if (doc.HasParseError())
    {
        _res.statusCode = ResponseCode::PARSING_ERROR;
        _res.message = "Parsing failed with error code " + std::string(GetParseError_En(doc.GetParseError()));
        return;
    }

    if (!doc.HasMember("games") || !doc["games"].IsArray()) {
        _res.statusCode = ResponseCode::MISSING_FIELD_ERROR;
        _res.message = "JSON does not contain a valid 'games' array field.\n";
        return;
    }

    const Value& gamesArray = doc["games"];

    if (gamesArray.Empty()) {
        // No popup, just display a a message on the screen
        _res.statusCode = ResponseCode::NO_GAMES_FOUND;
        _res.message = "No games played yet !";
        return;
    }
    // Iterate over the array and do whatever you need with each game object
    for (SizeType i = 0; i < gamesArray.Size(); ++i) {
        const Value& game = gamesArray[i];
        GamesData gameData;

        // get white username and rating
        if ((gameData.whiteUsername = extractString(game["white"], "username")) == "")
        {
            _res.statusCode = ResponseCode::DATA_EXTRACTION_ERROR;
            _res.message = "Unable to get white username\n";
        }
        if ((gameData.whiteRating = extractInt(game["white"], "rating")) == "")
        {
            _res.statusCode = ResponseCode::DATA_EXTRACTION_ERROR;
            _res.message = "Unable to get white rating\n";
        }
        // get black username and rating
        if ((gameData.blackUsername = extractString(game["black"], "username")) == "")
        {
            _res.statusCode = ResponseCode::DATA_EXTRACTION_ERROR;
            _res.message = "Unable to get black username\n";
        }
        if ((gameData.blackRating = extractInt(game["black"], "rating")) == "")
        {
            _res.statusCode = ResponseCode::DATA_EXTRACTION_ERROR;
            _res.message = "Unable to get black rating\n";
        }
        // get time_class
        if ((gameData.timeClass = extractString(game, "time_class")) == "")
        {
            _res.statusCode = ResponseCode::DATA_EXTRACTION_ERROR;
            _res.message = "Unable to get time class\n";
        }
        //get pgn
        if ((gameData.pgn = extractString(game, "pgn")) == "")
        {
            _res.statusCode = ResponseCode::DATA_EXTRACTION_ERROR;
            _res.message = "Unable to get pgn\n";
        }
        // find if player has played as white or black and display if he won or lost the game.
        if (gameData.whiteUsername == username)
            gameData.result = game["white"]["result"] != "win" ? "Lost" : "Won";
        else
            gameData.result = game["black"]["result"] != "win" ? "Lost" : "Won";

        // insert this game data in the vector
        _gamesData.push_back(gameData);
    }
    _res.statusCode = ResponseCode::OK;
}

//------------------------------------------------------------------------------
/**
*/
const Response&
Logic::GamesPlayedWithinPeriod(const std::string& username, const std::string& year, const std::string& month)
{
    std::string url = "https://api.chess.com/pub/player/" + to_lower(username) + "/games/" + year + '/' + month;
    cpr::Response res = cpr::Get(cpr::Url{ url });
    Document doc;

    if (res.status_code == cpr::status::HTTP_NOT_FOUND)
    {
        _res.statusCode = NO_GAMES_FOUND;
        _res.message = "No games played yet !";
        return _res;
    }

    doc.Parse(res.text.c_str());
    GetInfosFromListOfGamesPlayed(username, doc);
    _res.gamesData = _gamesData;
    return _res;
}

}
