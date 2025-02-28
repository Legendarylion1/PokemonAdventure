#include "Texture.h"

/// <summary>
/// Creates a texture that can be bound to a VAO
/// </summary>
/// <param name="image">- file location of the image texture</param>
/// <param name="texType">- Type of texture to create</param>
/// <param name="slot">- Texture slot to be used</param>
/// <param name="format">- RGB format of the image</param>
/// <param name="pixelType">- The data type the information is being stored with</param>
Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//GLRGB for jpeg
	//GLRGBA for png
	glTexImage2D(texType, 0, GL_RGBA8, widthImg, heightImg, 0, format, pixelType, bytes);

	glGenerateMipmap(texType);
	stbi_image_free(bytes);
	glBindTexture(texType, 0);


}

/// <summary>
/// Creates a texture object as a placeholder
/// </summary>
Texture::Texture()
{
	//To help initialize empty array in gameMap
}

/// <summary>
/// Binds the texUnit uniform for the texture
/// </summary>
/// <param name="shader">- Reference to the game's shader</param>
/// <param name="uniform">- The name of the uniform to be bound</param>
/// <param name="unit">- Value to bind to the uniform</param>
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(tex0Uni, unit);
}

/// <summary>
/// Binds the texture for use
/// </summary>
void Texture::Bind()
{
	glBindTexture(type, ID);
}

/// <summary>
/// Unbinds the texture
/// </summary>
void Texture::Unbind()
{
	glBindTexture(type, 0);
}

/// <summary>
/// Deletes the texture from the GPU
/// </summary>
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}