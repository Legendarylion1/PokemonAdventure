#include "ShaderClass.h"

/// <summary>
/// Reads a file for its contents
/// </summary>
/// <param name="fileName">- Filepath of the file to read</param>
/// <returns>String of the file contents</returns>
std::string getFileContents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return (contents);
	}
	throw(errno);
}

/// <summary>
/// Compiles the vertex and fragment shaders
/// </summary>
/// <param name="vertexFile">- Filepath of the vertex shader</param>
/// <param name="fragFile">- File path of the fragment shader</param>
Shader::Shader(const char* vertexFile, const char* fragFile)
{
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "Vertex Shader");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "Fragment Shader");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "Shader Program");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader():
	ID(0)
{
}

/// <summary>
/// Activates the shader for use
/// </summary>
void Shader::Activate()
{
	glUseProgram(ID);
}

/// <summary>
/// Deletes the shader from the GPU
/// </summary>
void Shader::Delete()
{
	glDeleteProgram(ID);
}

/// <summary>
/// Prints any errors during compilation of the shader
/// </summary>
/// <param name="shader">ID of the shader</param>
/// <param name="type"> Name of the file being compiled</param>
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for: " << type << "\n" << std::endl;
		}
	}
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for: " << type << "\n" << std::endl;
		}
	}
}