#include "../../include/App/ChessBoard.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace Stuckfish
{
	ImTextureID ChessBoard::LoadTextureFromFile(const char* filename)
	{
        int width, height, channels;
        unsigned char* data = stbi_load(filename, &width, &height, &channels, 4); // Load image with 4 channels (RGBA)
        if (data == nullptr) {
            printf("Failed to load texture from file: %s\n", filename);
            return nullptr;
        }

        printf("Loaded texture: %s, Width: %d, Height: %d, Channels: %d\n", filename, width, height, channels);

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        return (ImTextureID)(intptr_t)textureID;
	}

    void ChessBoard::LoadPiecesTexture()
    {
        _pieceTextures['P'] = LoadTextureFromFile("assets/pieces/white_pawn.png");
        _pieceTextures['p'] = LoadTextureFromFile("assets/pieces/black_pawn.png");
        _pieceTextures['R'] = LoadTextureFromFile("assets/pieces/white_rook.png");
        _pieceTextures['r'] = LoadTextureFromFile("assets/pieces/black_rook.png");
        _pieceTextures['N'] = LoadTextureFromFile("assets/pieces/white_knight.png");
        _pieceTextures['n'] = LoadTextureFromFile("assets/pieces/black_knight.png");
        _pieceTextures['B'] = LoadTextureFromFile("assets/pieces/white_bishop.png");
        _pieceTextures['b'] = LoadTextureFromFile("assets/pieces/black_bishop.png");
        _pieceTextures['Q'] = LoadTextureFromFile("assets/pieces/white_queen.png");
        _pieceTextures['q'] = LoadTextureFromFile("assets/pieces/black_queen.png");
        _pieceTextures['K'] = LoadTextureFromFile("assets/pieces/white_king.png");
        _pieceTextures['k'] = LoadTextureFromFile("assets/pieces/black_king.png");

    }
}
