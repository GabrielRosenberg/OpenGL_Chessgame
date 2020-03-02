#include "Game.h"
#include "game/chess_pieces/chessPiece.h"
#include "reactphysics3d.h"


using namespace reactphysics3d;

Game::Game(GLuint width, GLuint height) : width(width), height(height), chessBoard(8,std::vector<ChessPiece*>(8, nullptr))
{
}

Game::~Game()
{
}

void Game::init()
{
    rp3d::CollisionWorld world;
	
	ResourceManager::loadModel("src/resources/objects/sphere.obj", "sphere");
	ResourceManager::loadModel("src/resources/objects/board/chessboard.obj", "board");
	ResourceManager::loadModel("src/resources/objects/chessPieces/pawn.obj", "pawn");
	ResourceManager::loadModel("src/resources/objects/chessPieces/bishop.obj", "bishop");
	ResourceManager::loadModel("src/resources/objects/chessPieces/king.obj", "king");
	ResourceManager::loadModel("src/resources/objects/chessPieces/queen.obj", "queen");
	ResourceManager::loadModel("src/resources/objects/chessPieces/knight.obj", "knight");
	ResourceManager::loadModel("src/resources/objects/chessPieces/rook.obj", "rook");
	
	ResourceManager::loadShader("src/shaders/pbr_texture_vs.glsl", "src/shaders/pbr_texture_fs.glsl", "boardShader");
	ResourceManager::loadShader("src/shaders/pbr_color_vs.glsl", "src/shaders/pbr_color_fs.glsl", "pieceShader");
	ResourceManager::loadShader("src/shaders/light_vertex_shader.glsl", "src/shaders/light_fragment_shader.glsl", "lightShader");

    glm::mat4 projection = glm::perspective(glm::radians(25.0f), (float)width / (float)height, 0.1f, 100.0f);
    glm::vec3 lightPos = glm::vec3(1.5f, 0.9f, .5f);
	
	ResourceManager::getShader("boardShader").use();
    ResourceManager::getShader("boardShader").setFloat("metallic", 1.0f);
    ResourceManager::getShader("boardShader").setFloat("roughness", 0.4f);
    ResourceManager::getShader("boardShader").setFloat("ao", 1.0f);
    ResourceManager::getShader("boardShader").setMat4("projection", projection);
    ResourceManager::getShader("boardShader").setVec3("lightPos", lightPos);
	

	ResourceManager::getShader("pieceShader").use();
    ResourceManager::getShader("pieceShader").setFloat("metallic", 0.1f);
    ResourceManager::getShader("pieceShader").setFloat("roughness", 0.1f);
    ResourceManager::getShader("pieceShader").setFloat("ao", 0.1f);
    ResourceManager::getShader("pieceShader").setMat4("projection", projection);
    ResourceManager::getShader("pieceShader").setVec3("lightPos", lightPos);
	

	ResourceManager::getShader("lightShader").use();
	ResourceManager::getShader("lightShader").setMat4("projection", projection);

	Player player = WhitePlayer;
        for (int y = 0; y < 8; y+=7) {
            chessBoard[y][0] = new ChessPiece(0, y, player, "rook", "pieceShader");
            chessBoard[y][1] = new ChessPiece(1, y, player, "knight", "pieceShader");
            chessBoard[y][2] = new ChessPiece(2, y, player, "bishop", "pieceShader");
            chessBoard[y][3] = new ChessPiece(3, y, player, "queen", "pieceShader");
            chessBoard[y][4] = new ChessPiece(4, y, player, "king", "pieceShader");
            chessBoard[y][5] = new ChessPiece(5, y, player, "bishop", "pieceShader");
            chessBoard[y][6] = new ChessPiece(6, y, player, "knight", "pieceShader");
            chessBoard[y][7] = new ChessPiece(7, y, player, "rook", "pieceShader");
            for (int x = 0; x < 8; x++) {
                int pawnY = y + (player == WhitePlayer ? 1 : -1);
                chessBoard[pawnY][x] = new ChessPiece(x, pawnY, player, "pawn", "pieceShader");
            }
            player = BlackPlayer;
        }
}

void Game::processInput(GLfloat dt)
{
}

void Game::update(GLfloat dt)
{
}

void Game::render()
{
	glm::vec3 lightPos = glm::vec3(1.5f, 0.9f, .5f);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera.GetViewMatrix();
    ResourceManager::getShader("boardShader").use();
    ResourceManager::getShader("boardShader").setMat4("view", view);
    ResourceManager::getShader("boardShader").setVec3("viewPos", camera.Position);
    ResourceManager::getShader("boardShader").setMat4("model", model);
    ResourceManager::getModel("board").draw(ResourceManager::getShader("boardShader"));

	ResourceManager::getShader("pieceShader").use();
    ResourceManager::getShader("pieceShader").setMat4("view", view);
    ResourceManager::getShader("pieceShader").setVec3("viewPos", camera.Position);

	
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(.1));
    ResourceManager::getShader("lightShader").use();
    ResourceManager::getShader("lightShader").setMat4("view", view);
    ResourceManager::getShader("lightShader").setMat4("model", model);
    ResourceManager::getModel("sphere").draw(ResourceManager::getShader("lightShader"));
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (chessBoard[i][j] != nullptr)
				chessBoard[i][j]->render();
		}
	}
	
}
