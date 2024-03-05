#pragma once
#include "Camera.h"
#include "WorldObject.h"
class PlayerCharacter : public WorldObject
{
	public:
	//constructor(s)
	PlayerCharacter(std::vector<float>& InVertices, glm::vec3 InPos, glm::vec3 InSize = glm::vec3(2, 2, 2), glm::vec3 InRGB = glm::vec3(1.f, 0.9f, 0.8f));

	//the player character's original position
	glm::vec3 OriginalPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	//function to render the player character
	void Render(const unsigned int& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices) override;

	//function to process input
	void ProcessInput(Camera InCamera, Camera_Movement CameraDirection, float DeltaTime);
};

