#include "ResourceManager.h"

std::map<std::string, Model> ResourceManager::models;
std::map<std::string, Shader> ResourceManager::shaders;

void ResourceManager::loadModel(const char* path, std::string name)
{
	Model model;
	model.loadModel(path);
	models[name] = model;
}

Model& ResourceManager::getModel(std::string name)
{
	return models[name];
}

void ResourceManager::loadShader(const char* vertexPath, const char* fragmentPath, std::string name)
{
	Shader shader;
	shader.loadShader(vertexPath, fragmentPath);
	shaders[name] = shader;
}

Shader& ResourceManager::getShader(std::string name)
{
	return shaders[name];
}
