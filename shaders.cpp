#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "shader/shaders.h"

void Shader::use() { glUseProgram(program); }

void Shader::setint(const char* name, int* valueptr) { glUniform1i(glGetUniformLocation(program, name), *valueptr); }
void Shader::set2i(const char* name, int* valueptr) { glUniform2i(glGetUniformLocation(program, name), *valueptr, *(valueptr + 1)); }
void Shader::setfloat(const char* name, float* valueptr) { glUniform1f(glGetUniformLocation(program, name), *valueptr); }
void Shader::set2f(const char* name, float* valueptr) { glUniform2f(glGetUniformLocation(program, name), *valueptr, *(valueptr + 1)); }
void Shader::set3f(const char* name, float* valueptr) { glUniform3f(glGetUniformLocation(program, name), *valueptr, *(valueptr + 1), *(valueptr + 2)); }
void Shader::set4f(const char* name, float* valueptr) { glUniform4f(glGetUniformLocation(program, name), *valueptr, *(valueptr + 1), *(valueptr + 2), *(valueptr + 3)); }
void Shader::setmat4(const char* name, const float* valueptr) { glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, valueptr); }

std::string copyFromFile(const std::filesystem::path& p)
{
	std::ifstream shaderfile;
	std::stringstream dataBuffer;

	shaderfile.open(p, std::ios::in);
	if (!shaderfile.is_open())
	{
		std::cerr << "ERROR::SHADER::FILE_OPENING_FAILED\n";
	}

	dataBuffer << shaderfile.rdbuf();

	shaderfile.close();

	return dataBuffer.str();
}

bool compileShader(unsigned int shader, const char* data)
{
	glShaderSource(shader, 1, &data, NULL);

	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << '\n';
		return false;
	}

	return true;
}

int shaderType(char charDef)
{
	switch (charDef)
	{
	// VERTEX
	case 'v':	return 0x8B31;
	// FRAGMENT
	case 'f':	return 0x8B30;
	// GEOMETRY
	case 'g':	return 0x8DD9;

	default:
		std::cerr << "UNKNOWN SHADER_TYPE WITH BASE " << charDef << '\n';
		return -1;
	}
}

void Shader::create(const char* shadersPath)
{
	program = glCreateProgram();

	for (const std::filesystem::directory_entry& dir : std::filesystem::recursive_directory_iterator(shadersPath))
	{
		unsigned int shader;
		shader = glCreateShader(shaderType(dir.path().stem().string()[0]));

		compileShader(shader, copyFromFile(dir.path()).c_str());

		glAttachShader(program, shader);
		glDeleteShader(shader);
	}

	glLinkProgram(program);

	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER_PROGRAM::LINKING_FAILED" << infoLog << '\n';
	}
}

Shader::Shader(const char* shadersPath)
{
	Shader::create(shadersPath);
}