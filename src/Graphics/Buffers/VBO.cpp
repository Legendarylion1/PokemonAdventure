#include "VBO.h"

/// <summary>
/// Binds the buffer data to the ID of the VBO given by the GPU
/// </summary>
/// <param name="vertices">- number of vertices</param>
/// <param name="size">- Size in byes of the vertices</param>
VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

/// <summary>
/// Binds the buffer for use
/// </summary>
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

/// <summary>
/// Unbinds the buffer
/// </summary>
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/// <summary>
/// Deletes the buffer from the GPU
/// </summary>
void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}