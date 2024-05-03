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
    if (!doc.HasParseError()) {
        if (doc.HasMember("games") && doc["games"].IsArray()) {
            const Value& gamesArray = doc["games"];

            if (gamesArray.Empty()) {
                // display on the window "No games found"
                // Log in the local console the same thing
                std::cout << "No games found !\n";
                return;
            }
            // Iterate over the array and do whatever you need with each game object
            for (SizeType i = 0; i < gamesArray.Size(); ++i) {
                const Value& game = gamesArray[i];
                GamesData gameData;

                // get white username and rating
                if ((gameData.whiteUsername = extractString(game["white"], "username")) == "")
                    std::cerr << "Unable to get white username\n";
                if ((gameData.whiteRating = extractInt(game["white"], "rating")) == "")
                    std::cerr << "Unable to get white rating\n";

                // get black username and rating
                if ((gameData.blackUsername = extractString(game["black"], "username")) == "")
                    std::cerr << "Unable to get black username\n";
                if ((gameData.blackRating = extractInt(game["black"], "rating")) == "")
                    std::cerr << "Unable to get black rating\n";

                // get time_class
                if ((gameData.timeClass = extractString(game, "time_class")) == "")
                    std::cerr << "Unable to get time class\n";

                //get pgn
                if ((gameData.pgn = extractString(game, "pgn")) == "")
                    std::cerr << "Unable to get png\n";

                // find if player has played as white or black and display if he won or lost the game.
                if (gameData.whiteUsername == username)
                    gameData.gameResult = game["white"]["result"] != "win" ? "Lost" : "Won";
                else
                    gameData.gameResult = game["black"]["result"] != "win" ? "Lost" : "Won";    

                // insert this game data in the vector
                _gamesData.push_back(gameData);
            }
        }
        else {
            std::cerr << "JSON does not contain a valid 'games' array field." << std::endl;
            return;
        }
    }
    else {
        std::cerr << "Parsing failed with error code " << GetParseError_En(doc.GetParseError()) << std::endl;
        return;
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Logic::GamesPlayedWithinPeriod(const std::string& username, const std::string& year, const std::string& month)
{
    std::string url = "https://api.chess.com/pub/player/" + to_lower(username) + "/games/" + year + '/' + month;
    cpr::Response res = cpr::Get(cpr::Url{ url });

    if (res.status_code == cpr::status::HTTP_OK) {
        Document doc;
        doc.Parse(res.text.c_str());
        GetInfosFromListOfGamesPlayed(username, doc);
    } else {
        std::cerr << "Request failed with status code: " << res.status_code << std::endl;
        return;
    }

    for (auto g : _gamesData) {
        std::cout << "White username: " << g.whiteUsername << '(' << g.whiteRating << ")\n";
        std::cout << "Black username: " << g.blackUsername << '(' << g.blackRating << ")\n";
        std::cout << "Game Result: " << g.gameResult << "\n\n";
    }
    return;
}

}
