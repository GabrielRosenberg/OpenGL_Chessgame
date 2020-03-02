#pragma once
#include <vector>
#include <ostream>
#include "ResourceManager.h"
#include "reactphysics3d.h"


enum Player {
	WhitePlayer = 0,
	BlackPlayer = 1
};

struct Pos {
	unsigned int x = 0;
	unsigned int y = 0;

	Pos() = default;;

	Pos(unsigned int x, unsigned int y) : x(x), y(y) {}
};

class ChessPiece {
protected:
	Player player;
	Pos pos;
	std::string shader;
	std::string model;
	rp3d::CollisionBody* collisionObject;

public:
	ChessPiece() : player(WhitePlayer), pos(0,0), shader(""), model(""){};
	
	ChessPiece(int x, int y, Player player, std::string model, std::string shader, rp3d::CollisionWorld* collisionWorld) : pos(x, y), player(player), model(model), shader(shader)
	{
		rp3d::Vector3 initPosition(x, y, 0.0); 
		rp3d::Quaternion initOrientation = rp3d::Quaternion::identity(); 
		rp3d::Transform transform(initPosition, initOrientation);
		collisionObject = collisionWorld->createCollisionBody(transform);
		const rp3d::CapsuleShape capsuleShape(1.0, 2.0);
	}

	std::vector<Pos> getMoves(ChessPiece* board[8][8]);

	Player getPlayer() {
		return player;
	}

	std::string toString() {
		if (player == WhitePlayer) 
			return " |white " + model + "| ";
		else
			return " |white " + model + "| ";
	}

	void render()
	{
		glm::vec3 color = player == WhitePlayer ? glm::vec3(.9, .9, .9) : glm::vec3(.0, .0, .0);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.1f*pos.x, 0.0f, 0.1f*pos.y));
		if (player == WhitePlayer)
		{
			model = glm::translate(model, glm::vec3(0.0f, 0.5f * pos.y, 0.0f)); 
			model = glm::rotate(model, glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)); 
			model = glm::translate(model, glm::vec3(0.0f, -0.5f * pos.y, 0.0f));
		}
		ResourceManager::getShader(shader).use();
		ResourceManager::getShader(shader).setMat4("model", model);
		ResourceManager::getShader(shader).setVec3("material.albedo", color);
		ResourceManager::getModel(this->model).draw(ResourceManager::getShader(shader));
	}
};