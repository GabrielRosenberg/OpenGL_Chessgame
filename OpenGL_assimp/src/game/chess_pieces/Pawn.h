#pragma once
#include "chessPiece.h"
#include <tuple>

class Pawn : public ChessPiece {
private:
    bool hasMoved = false;

public:

	Pawn(int x, int y, Player player, Model* model, Shader* shader) : ChessPiece(x, y, player, model, shader) {};

    std::vector<Pos> getMoves(ChessPiece* board[8][8]) override {
        std::vector<Pos> possibleMoves;

        int dir = player ? -1 : 1;

        if (board[pos.y + dir][pos.x] == NULL)                            // Om rutan man vill gå till är tom
            possibleMoves.push_back(Pos(pos.y + dir, pos.x));             // Returnera True om rutan är precis framför

        if (!hasMoved && board[pos.y + dir * 2][pos.x] == NULL)
            possibleMoves.push_back(Pos(pos.y + dir * 2, pos.x));

        if (board[pos.y + dir][pos.x + 1] != NULL && board[pos.y + dir][pos.x + 1]->getPlayer() == !player)
            possibleMoves.push_back(Pos(pos.y + dir, pos.x + 1));

        if (board[pos.y + dir][pos.x + 1] != NULL && board[pos.y + dir][pos.x - 1]->getPlayer() == !player)
            possibleMoves.push_back(Pos(pos.y + dir, pos.x - 1));

        return possibleMoves;
    }
};