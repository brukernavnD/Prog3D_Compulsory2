#include "Vertex.h"

Vertex::Vertex()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	RGB = glm::vec3(1.0f, 1.0f, 1.0f);
}

Vertex::Vertex(glm::vec3 InPos, glm::vec3 InRGB)
{
	Position = InPos;
	RGB = InRGB;
}
