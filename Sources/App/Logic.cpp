#include "../../Libraries/include/Logic.hpp"

using namespace rapidjson;

static std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
    return s;
}

static std::string extractField(const Value& jsonObject, const std::string& fieldName) {
    if (jsonObject.HasMember(fieldName.c_str()) && jsonObject[fieldName.c_str()].IsString()) {
        return jsonObject[fieldName.c_str()].GetString();
    }
    return ""; // Return empty string if field not found or not a string
}

namespace Stuckfish
{
	bool Logic::IsChessDotComUser(const std::string& username)
	{
        std::string url = "https://api.chess.com/pub/player/" + to_lower(username);
        cpr::Response res = cpr::Get(cpr::Url{ url });

        if (res.status_code == cpr::status::HTTP_OK)
        {
            return true;
        }
        return false;
	}

    void Logic::GamesPlayedWithinPeriod(const std::string& username, const std::string& year, const std::string& month)
    {
        std::string url = "https://api.chess.com/pub/player/" + to_lower(username) + "/games/" + year + '/' + month;

        cpr::Response res = cpr::Get(cpr::Url{ url });

        if (res.status_code == cpr::status::HTTP_OK)
        {
            rapidjson::Document doc;
            doc.Parse(res.text.c_str());

            // Check if parsing succeeded
            if (!doc.HasParseError())
            {

                // Check if the JSON contains the field "a"
                if (doc.HasMember("games") && doc["games"].IsArray())
                {
                    const Value& gamesArray = doc["games"];

                    if (gamesArray.Empty())
                    {
                        // display on the window "No games found"
                        // Log in the local console the same thing
                        std::cout << "No games found !\n";
                        return;
                    }
                    // Iterate over the array and do whatever you need with each game object
                    for (SizeType i = 0; i < gamesArray.Size(); ++i) {
                        const Value& game = gamesArray[i];
 
                        // TODO: refactor this and handle exceptions.
                        // get white username and rating -- Either create method to extract field or a specific method to get players infos.
                        if (game.HasMember("white") && game["white"].HasMember("username") &&
                            game["white"].HasMember("rating"))
                        {
                            _whiteUsername = game["white"]["username"].GetString();
                            _whiteRating = std::to_string(game["white"]["rating"].GetInt());

                            std::cout << "White infos: " << _whiteUsername << '(' << _whiteRating << ')' << std::endl;
                        }
                        // get black username and rating
                        if (game.HasMember("black") && game["black"].HasMember("username") &&
                            game["black"].HasMember("rating"))
                        {
                            _blackUsername = game["black"]["username"].GetString();
                            _blackRating = std::to_string(game["black"]["rating"].GetInt());

                            std::cout << "Black infos: " << _blackUsername << '(' << _blackRating << ')' << std::endl;
                        }
                        // get time_class
                        if (game.HasMember("time_class") && game["time_class"].IsString())
                        {
                            _gameFormat = game["time_class"].GetString();

                            std::cout << "Game format: " << _gameFormat << std::endl;
                        }
                        //get pgn
                        if (game.HasMember("pgn") && game["pgn"].IsString())
                        {
                            _pgn = game["pgn"].GetString();
                            //std::cout << "Pgn: " << _pgn;
                        }

                        // find if player has played as white or black and display if he won or lost the game.
                        if (_whiteUsername == username)
                        {
                            if (game["white"]["result"] != "win")
                            {
                                // Print the result on the button
                                std::cout << "Status: lost !\n";
                            }
                            else
                            {
                                std::cout << "Status: Won !\n";
                            }
                        }
                        else
                        {
                            if (game["black"]["result"] != "win")
                            {
                                // Print the result on the button
                                std::cout << "Status: lost !\n";
                            }
                            else
                            {
                                std::cout << "Status: Won !\n";
                            }
                        }
                        std::cout << "\n";
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
        else {
            std::cerr << "Request failed with status code: " << res.status_code << std::endl;
            return;
        }
        return;
    }
}