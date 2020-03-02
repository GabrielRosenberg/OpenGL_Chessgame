#pragma once
#include <string>
#include <iostream>
#include "chess_pieces/chessPiece.h"
#include "chess_pieces/Pawn.h"

class ChessModel {
private:
	std::string message;
	ChessPiece* board[8][8]{nullptr};
	Player playerTurn = WhitePlayer;


public:
	ChessModel() {
		Player assignedPlayer = WhitePlayer;
		/*for (int i = 0; i < 8; i++) 
			board[0][i] = new Pawn(0, i, assignedPlayer, &pawnModel, &chessPieceShader);*/

		for (int i = 1; i < 8; i++) 
			for (int j = 0; j < 8; j++)
				board[i][j] = nullptr;
	}

	void draw() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++)
				std::cout << "  " + getStatus(j, i); // getStatus
			std::cout << std::endl;
		}
	}

	std::string getStatus(int x, int y) {
		if (board[y][x] != nullptr)
			return board[y][x]->toString();
		else
			return ".";
	}
};