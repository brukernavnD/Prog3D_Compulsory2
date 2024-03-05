#include "WorldObject.h"

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "glm/gtx/transform.hpp"

WorldObject::WorldObject()
{
}

WorldObject::WorldObject(glm::vec3 InPos, glm::vec3 InRGB, glm::vec3 InSize)
{
	Position = InPos;
	RGB = InRGB;
	Size = InSize;
}


void WorldObject::Render(const unsigned int& InShaderProgram, const std::string& ModelKey, std::vector<float>& InVertices)
{
	//create an identity matrix
    glm::mat4 model = glm::mat4(1.0f);

	//do the translation
	model = translate(model, Position);

	//do the rotation
	model = rotate(model, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = rotate(model, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = rotate(model, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	//do the scaling
	model = scale(model, Size);

	//set the ModelMatrix property
	ModelMatrix = model;

	//set the model matrix
	glUniformMatrix4fv(glGetUniformLocation(InShaderProgram, ModelKey.c_str()), 1, GL_FALSE, &model[0][0]);

	//draw our vertices
	glDrawArrays(GL_TRIANGLES, VertexIndex, MyVertices.size() / 6);
}
