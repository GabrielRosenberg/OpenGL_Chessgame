#pragma once
#include  <vector>
#include <map>
#include <string>
#include "Model.h"

class ResourceManager
{
public:
	static void loadModel(const char* path, std::string name);
	static Model& getModel(std::string name);
	
	static void loadShader(const char* vertexPath, const char* fragmentPath, std::string name);
	static Shader& getShader(std::string name);
private:
	static std::map<std::string, Model> models;
	static std::map<std::string, Shader> shaders;
};

