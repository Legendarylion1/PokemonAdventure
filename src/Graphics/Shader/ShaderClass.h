#pragma once

#include <GL/glew.h>
#include<string>
#include <fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string getFileContents(const char* fileName);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);
	Shader();
	void Activate();
	void Delete();
private:
	void compileErrors(unsigned int shader, const char* type);

};