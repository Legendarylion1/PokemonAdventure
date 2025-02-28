#include "VAO.h"

/// <summary>
/// Creates a vao and gets assigned an ID from the GPU
/// </summary>
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

/// <summary>
/// Links a VBO to the VAO
/// </summary>
/// <param name="VBO">- Desired VBO to link</param>
/// <param name="layout">- Shader location of the VBO values</param>
/// <param name="numComponents">- How many values are being used by the VBO</param>
/// <param name="type">- Type of values being used by the VBO</param>
/// <param name="stride">- How far apart are the total set of values</param>
/// <param name="offset">- How far from the start of the set are the desired VBO values</param>
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

/// <summary>
/// Bind the VAO for use
/// </summary>
void VAO::Bind()
{
	glBindVertexArray(ID);
}

/// <summary>
/// Unbind the VAO
/// </summary>
void VAO::Unbind()
{
	glBindVertexArray(0);
}

/// <summary>
/// Delete the VAO from the GPU
/// </summary>
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}