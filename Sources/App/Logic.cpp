#include "../../Libraries/include/Logic.hpp"


static std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
    return s;
}

namespace Stuckfish
{
	bool Logic::IsChessComUser(const std::string& username)
	{
        std::string url = "https://api.chess.com/pub/player/" + to_lower(username);
        cpr::Response res = cpr::Get(cpr::Url{url});

        if (res.status_code == HttpStatusCode::SUCCESS)
        {
            return true;
        }
        return false;
	}
}