#pragma once

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h>
#include "../Imgui.hpp"

#include <unordered_map>
#include "../Utils.h"

namespace Stuckfish
{
	class ChessBoard
	{
	public:
		ImTextureID LoadTextureFromFile(const char* filename);
		void LoadPiecesTexture();
		
		const std::string& getStartingPosition()
		{ return _startingPositionFen; }
		const std::unordered_map<char, ImTextureID>& getPiecesTextures()
		{ return _pieceTextures; }
		
		void draw(void);
		void drawPieces(void);

	private:
		const std::string _startingPositionFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
		const std::unordered_map<std::string, std::string> _moveClassificationColor = {
			{ "brilliant", "#1baaa6" },
			{ "great", "#5b8baf" },
			{ "best", "#98bc49" },
			{ "excellent", "#98bc49" },
			{ "good", "#97af8b" },
			{ "inaccuracy", "#f4bf44" },
			{ "mistake", "#e28c28" },
			{ "blunder", "#c93230" },
			{ "forced", "#97af8b" },
			{ "book", "#a88764" },
		};
		std::unordered_map<char, ImTextureID> _pieceTextures;
	};
}

