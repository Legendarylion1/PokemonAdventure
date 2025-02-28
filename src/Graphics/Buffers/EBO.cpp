#include "EBO.h"

/// <summary>
/// Creates an index buffer object
/// </summary>
/// <param name="indices">Pointer to the indice array</param>
/// <param name="size">Total size of the indice array</param>
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

/// <summary>
/// Binds the EBO for use
/// </summary>
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

/// <summary>
/// Unbinds the EBO
/// </summary>
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/// <summary>
/// Deletes the EBO
/// </summary>
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}