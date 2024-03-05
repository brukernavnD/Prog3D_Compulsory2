#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "glm/gtx/transform.hpp"
#include "Vertex.h"

class WorldObject
{
public:
	virtual ~WorldObject() = default;

	//constructor(s)
	WorldObject();
	WorldObject(glm::vec3 InPos, glm::vec3 InRGB, glm::vec3 InSize);

	//our position
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);

	//our rotation
	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

	//our colour
	glm::vec3 RGB = glm::vec3(0.0f, 0.0f, 0.0f);

	//our size
	glm::vec3 Size = glm::vec3(1.0f, 1.0f, 1.0f);

	//the index our vertices are stored at in the vertecies array
	int VertexIndex = 0;

	//the vertices of the object (in the form of floats)
	std::vector<float> MyVertices;

	//storage for the model matrix
	glm::mat4 ModelMatrix = glm::mat4(1.0f);

	//function to render the object
	virtual void Render(const unsigned int& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices);
};

