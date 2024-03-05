#pragma once
#include "WorldObject.h"

class House : public WorldObject
{
public:

	//floor variables
	float FloorSize = 10.0f;
	float FloorHeight = 0.0f;
	glm::vec3 FloorColour = glm::vec3(0.0f, 1.0f, 0.0f);

	//general wall variables
	float WallHeight = 1 / 2.0f;
	glm::vec3 WallColour = glm::vec3(1.0f, 1.0f, 1.0f);

	//wall proportions
	float FrontBackWallWidth = 4;
	float SideWallWidth = 4;

	//roof variables
	float RoofAngle = 45.f;
	glm::vec3 RoofColour = glm::vec3(0.5f, 0.5f, 0.5f);

	//door variables
	float DoorWidth = 1 * 2.0f / 3.0f;
	glm::vec3 DoorColour = glm::vec3(0.5f, 0.5f, 0.5f);

	//whether or not the door is open
	bool CheckDoorCollision = true;

	std::vector<float> DoorVertices =
	{
	    //door (first triangle)
	    -DoorWidth / 2.0f, FloorHeight, SideWallWidth / 2.0f, DoorColour.r, DoorColour.g, DoorColour.b,
	    DoorWidth / 2.0f, FloorHeight, SideWallWidth / 2.0f, DoorColour.r, DoorColour.g, DoorColour.b,
	    -DoorWidth / 2.0f, WallHeight, SideWallWidth / 2.0f, DoorColour.r, DoorColour.g, DoorColour.b,

	    //door (second triangle)
	    DoorWidth / 2.0f, FloorHeight, SideWallWidth / 2.0f, DoorColour.r, DoorColour.g, DoorColour.b,
	    -DoorWidth / 2.0f, WallHeight, SideWallWidth / 2.0f, DoorColour.r, DoorColour.g, DoorColour.b,
	    DoorWidth / 2.0f, WallHeight, SideWallWidth / 2.0f, DoorColour.r, DoorColour.g, DoorColour.b,
	};

	//constructor(s)
	House(glm::vec3 InPos, glm::vec3 InRGB, glm::vec3 InSize, std::vector<float>& InVertices);

	//function to render the house
	void Render(const unsigned int& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices) override;
};

