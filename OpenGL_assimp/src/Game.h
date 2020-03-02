#pragma once
#include <glad/glad.h>
#include "ResourceManager.h"
#include "camera.h"
#include "game/chess_pieces/chessPiece.h"

enum GameState {
    GameActive,
    GameMenu,
    GameWin
}; 

class Game
{
public:
    // Game state
    GameState  state;	
    GLboolean  keys[1024];
    GLuint	   width, height;
    std::vector<std::vector<ChessPiece*>> chessBoard;
	Camera camera;
	
    // Constructor/Destructor
    Game(GLuint width, GLuint height);
    ~Game();
    // Initialize game state (load all shaders/textures/levels)
    void init();
    // GameLoop
    void processInput(GLfloat dt);
    void update(GLfloat dt);
    void render();
};

