#pragma once
#include <string>
#include <vector>

#include "Vertex.h"
#include "WorldObject.h"
#include "glm/vec3.hpp"

class Pickup : public WorldObject
{
public:
	//constructor(s)
	Pickup(std::vector<float>& InVertices, glm::vec3 InPos, glm::vec3 InSize = glm::vec3(1, 1, 1), glm::vec3 InRGB = glm::vec3(1.f, 0.9f, 0.8f));
	
	//whether or not the pickup is active
	bool IsActive = true;

	//function to render the pickup
	void Render(const unsigned int& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices) override;
};

