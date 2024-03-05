#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(std::vector<float>& InVertices, glm::vec3 InPos, glm::vec3 InSize, glm::vec3 InRGB) : WorldObject(InPos, InRGB, InSize)
{
	//set the original position
	OriginalPosition = InPos;

	//create the vertices
	MyVertices = {
        //front side (first triangle)
        -0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],

        //front side (second triangle)
        0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],

        //back side (first triangle)
        -0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],

        //back side (second triangle)
        0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],

        //left side (first triangle)
        -0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],

        //left side (second triangle)
        -0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],

        //right side (first triangle)
        0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],

        //right side (second triangle)
        0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],

        //top side (first triangle)
        -0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
		0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
        -0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],

		//top side (second triangle)
		0.5f, 0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
		-0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
		0.5f, 0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],

		//bottom side (first triangle)
		-0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
		0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
		-0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],

		//bottom side (second triangle)
		0.5f, -0.5f, -0.5f, InRGB[0], InRGB[1], InRGB[2],
		-0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
		0.5f, -0.5f, 0.5f, InRGB[0], InRGB[1], InRGB[2],
	};

    //set the vertex index
     VertexIndex = InVertices.size() / 6;

	//check if our vertices are empty
	if (!MyVertices.empty())
	{
		//if they are, set them to the vertices passed in
		InVertices.insert(InVertices.end(), MyVertices.begin(), MyVertices.end());
	}
}

void PlayerCharacter::Render(const unsigned& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices)
{
	WorldObject::Render(InShaderProgram, ModelKey, InVertices);
}

void PlayerCharacter::ProcessInput(Camera InCamera, Camera_Movement CameraDirection, float DeltaTime)
{
	//calculate the velocity
    const float Velocity = InCamera.MovementSpeed * DeltaTime;

	//check if we're moving forward, backward, left, or right
	switch (CameraDirection)
	{
		case FORWARD:
			Position += InCamera.Front * Velocity;
			break;
		case BACKWARD:
			Position -= InCamera.Front * Velocity;
			break;
		case LEFT:
			Position -= InCamera.Right * Velocity;
			break;
		case RIGHT:
			Position += InCamera.Right * Velocity;
			break;
	}
}
