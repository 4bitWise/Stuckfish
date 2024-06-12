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
    void ChessBoard::draw(void)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 boardPos = ImGui::GetCursorScreenPos();

        for (int row = 0; row < CHESSBOARD_SIZE; ++row)
        {
            for (int col = 0; col < CHESSBOARD_SIZE; ++col)
            {
                // Calculate the position of the current tile and draw the tile
                ImU32 tileColor = ((row + col) % 2 == 0) ? whiteTileColor : blackTileColor;
                ImVec2 tilePos = ImVec2(boardPos.x + col * TILE_SIZE, boardPos.y + row * TILE_SIZE - 300);
                ImVec2 tileEndPos = ImVec2(tilePos.x + TILE_SIZE, tilePos.y + TILE_SIZE);
                drawList->AddRectFilled(tilePos, tileEndPos, tileColor);

                std::string coordText;
                /*if (row == 0) {
                    // Bottom row (a to h)
                    coordText = std::string(1, 'h' - col);
                }*/
                // Case where user has played as white.
                if (row == 7) {
                    // Top row (h to a)
                    coordText = std::string(1, 'a' + col);
                    ImVec2 letterPos = ImVec2(tilePos.x + TILE_SIZE - ImGui::CalcTextSize(coordText.c_str()).x - 2, tilePos.y + TILE_SIZE - ImGui::CalcTextSize(coordText.c_str()).y - 2);
                    drawList->AddText(letterPos, coordinatetextColor, coordText.c_str());
                }
                if (col == 0)
                {
                    // Draw the coordinates text
                    coordText = std::to_string(8 - row);
                    ImVec2 textPos = ImVec2(tilePos.x + 2, tilePos.y + 2);
                    drawList->AddText(textPos, coordinatetextColor, coordText.c_str());
                }
            }
        }
    }
 
    void ChessBoard::drawPieces(void)
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        int pieceRow = 0;
        int pieceCol = 0;
        ImVec2 boardPos = ImGui::GetCursorScreenPos();

        for (char c : _startingPositionFen) {
            if (c == '/') {
                pieceRow++;
                pieceCol = 0;
            }
            else if (isdigit(c)) {
                pieceCol += c - '0';
            }
            else {
                ImVec2 piecePos = ImVec2(boardPos.x + pieceCol * TILE_SIZE, boardPos.y + pieceRow * TILE_SIZE - 300);
                ImVec2 pieceEndPos = ImVec2(piecePos.x + TILE_SIZE, piecePos.y + TILE_SIZE);

                if (_pieceTextures.find(c) != _pieceTextures.end()) {
                    ImTextureID pieceTexture = _pieceTextures[c];
                    drawList->AddImage(pieceTexture, piecePos, pieceEndPos);
                }
                pieceCol++;
            }
        }
    }
}
