#include "House.h"

#include "glad/glad.h"

House::House(glm::vec3 InPos, glm::vec3 InRGB, glm::vec3 InSize, std::vector<float>& InVertices) : WorldObject(InPos, InRGB, InSize)
{
	//create the vertices
	MyVertices =
	{
		//back wall (first triangle)
	    - FrontBackWallWidth / 2, FloorHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, FloorHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //back wall (second triangle)
	    + FrontBackWallWidth / 2, FloorHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //left wall (first triangle)
	    - FrontBackWallWidth / 2, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, FloorHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //left wall (second triangle)
	    - FrontBackWallWidth / 2, FloorHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //right wall (first triangle)
	    + FrontBackWallWidth / 2, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, FloorHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //right wall (second triangle)
	    + FrontBackWallWidth / 2, FloorHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, WallHeight, - SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //front wall left of door (first triangle)
	    - FrontBackWallWidth / 2, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - DoorWidth / 2.0f, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //front wall left of door (second triangle)
	    - DoorWidth / 2.0f, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    - DoorWidth / 2.0f, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //front wall right of door (first triangle)
	    + DoorWidth / 2.0f, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + DoorWidth / 2.0f, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	    //front wall right of door (second triangle)
	    + FrontBackWallWidth / 2, FloorHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + DoorWidth / 2.0f, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,
	    + FrontBackWallWidth / 2, WallHeight, + SideWallWidth / 2.0f, WallColour.r, WallColour.g, WallColour.b,

	     //floor (first triangle)
	    -FloorSize, FloorHeight, -FloorSize, FloorColour.r, FloorColour.g, FloorColour.b,
	    FloorSize, FloorHeight, -FloorSize, FloorColour.r, FloorColour.g, FloorColour.b,
	    -FloorSize, FloorHeight, FloorSize, FloorColour.r, FloorColour.g, FloorColour.b,

	    //floor (second triangle)
	    FloorSize, FloorHeight, -FloorSize, FloorColour.r, FloorColour.g, FloorColour.b,
	    -FloorSize, FloorHeight, FloorSize, FloorColour.r, FloorColour.g, FloorColour.b,
	    FloorSize, FloorHeight, FloorSize, FloorColour.r, FloorColour.g, FloorColour.b,

		//left square of roof (first triangle)
	    -FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		-FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,

		//left square of roof (second triangle)
		-FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,

		//right square of roof (first triangle)
		FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,

		//right square of roof (second triangle)
		FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,

		//front triangle of roof (first triangle)
		-FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,

		//front triangle of roof (second triangle)
		FrontBackWallWidth / 2, WallHeight, -SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,

		//back triangle of roof (first triangle)
		-FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,

		//back triangle of roof (second triangle)
		FrontBackWallWidth / 2, WallHeight, +SideWallWidth / 2, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,
		0, WallHeight + (FrontBackWallWidth / 2) * tan(glm::radians(RoofAngle)), 0, RoofColour.r, RoofColour.g, RoofColour.b,
	};

	VertexIndex = InVertices.size() / 6;

	//check if our vertices are empty
	if (!MyVertices.empty())
	{
		//if they are, set them to the vertices passed in
		InVertices.insert(InVertices.end(), MyVertices.begin(), MyVertices.end());
		InVertices.insert(InVertices.end(), DoorVertices.begin(), DoorVertices.end());
	}

}

void House::Render(const unsigned& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices)
{
	WorldObject::Render(InShaderProgram, ModelKey, InVertices);

	//draw the door vertices
    if (CheckDoorCollision)
    {
		//set the model matrix
		glUniformMatrix4fv(glGetUniformLocation(InShaderProgram, ModelKey.c_str()), 1, GL_FALSE, &ModelMatrix[0][0]);

		//draw the door vertices
        glDrawArrays(GL_TRIANGLES, VertexIndex + MyVertices.size() / 6, DoorVertices.size() / 6);
	}
}
