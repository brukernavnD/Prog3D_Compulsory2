#include "NPC.h"

#include <iostream>
#include <ostream>

Path::Path(float InMovementSpeed, float(* InMathFunction)(float), float InLength, glm::vec3 InDirection): MovementSpeed(InMovementSpeed), MathFunction(InMathFunction), Length(InLength), Direction(InDirection)
{
		
}

NPC::NPC(std::vector<float>& InVertices, glm::vec3 InPos, glm::vec3 InSize, glm::vec3 InRGB) : WorldObject(InPos, InRGB, InSize)
{

    //set our original position
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

float NPC::MathFunction1(float Param)
{
	//get the value
	const float Value = 24.5210653286f * Param * Param -2.0635480065f * Param - 0.4835875541f;
	return Value;
}

float NPC::MathFunction2(float Param)
{
    //get the value
	const float Value = 0.5f * Param * Param - 0.5f * Param;
	return Value;
}

void NPC::Render(const unsigned& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices)
{
	WorldObject::Render(InShaderProgram, ModelKey, InVertices);
}

void NPC::Update(float DeltaTime)
{
	//check if we've reached the end of the path
    CheckForPathEnd();

	//move the npc towards the goal
	MoveTowardsGoal(DeltaTime);
}

void NPC::MoveTowardsGoal(float DeltaTime)
{
	//get the direction to the goal
	const glm::vec3 Direction = GetEndOfPath() - Position;

	//normalize the direction
	const glm::vec3 NormalizedDirection = normalize(Direction);

	//move the npc towards the goal
	Position += NormalizedDirection * DeltaTime * GetCurrentMovementSpeed();
}

void NPC::SwitchPath(Path* NewPathPtr)
{
    //check if the path is the same as the one we are switching to
    if (CurrentPathPtr == NewPathPtr)
    {
	    //if it is, return
		return;
	}

	//switch the path
	CurrentPathPtr = NewPathPtr;

    //reset the path progress direction
    PathProgressDirection = 1;
}

void NPC::CheckForPathEnd()
{
    //the minimum distance away from the end of the path before we switch paths
    constexpr float MinDistance = 0.1f;

	//get the distance between the npc and the end of the path
	const float Distance = distance(Position, GetEndOfPath());

	//check if either distance is less than the minimum distance
	if (Distance < MinDistance)
	{
		//reverse the direction of the path progress
		PathProgressDirection *= -1;
	}
}

glm::vec3 NPC::GetEndOfPath() const
{
	//check if the path progress direction is positive
	if (PathProgressDirection > 0)
	{
		//return the end of the current path
		return {OriginalPosition.x + CurrentPathPtr->Direction.x * CurrentPathPtr->MathFunction(CurrentPathPtr->Length), OriginalPosition.y + CurrentPathPtr->Direction.y * CurrentPathPtr->MathFunction(CurrentPathPtr->Length), OriginalPosition.z + CurrentPathPtr->Direction.z * CurrentPathPtr->MathFunction(CurrentPathPtr->Length)};
	}
	if (PathProgressDirection < 0)
	{
		//return the beginning of the current path
		return {OriginalPosition.x + CurrentPathPtr->Direction.x * CurrentPathPtr->MathFunction(0), OriginalPosition.y + CurrentPathPtr->Direction.y * CurrentPathPtr->MathFunction(0), OriginalPosition.z + CurrentPathPtr->Direction.z * CurrentPathPtr->MathFunction(0)};
	}

	//return zero vector
	return {0.0f, 0.0f, 0.0f};
}

float NPC::GetCurrentMovementSpeed() const
{
	return CurrentPathPtr->MovementSpeed;
}
