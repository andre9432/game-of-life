#ifndef SHADERS_H
#define SHADERS_H

// THIS FILE MUST BE CONTAINED IN A FOLDER NAMED "shader" in your include folder

class Shader
{
	unsigned int program{ 0 };

public:
	Shader(){}

	Shader(const char* shadersPath);

	void create(const char* shadersPath);

	void setint(const char* name, int* valueptr);
	void setfloat(const char* name, float* valueptr);

	/* MUST BE CONTIGUOUS IN MEMORY
	   INPUT FIRST VALUE IN ARRAY*/
	void set2i(const char* name, int* valueptr);
	void set2f(const char* name, float* valueptr);
	void set3f(const char* name, float* valueptr);
	void set4f(const char* name, float* valueptr);
	void setmat4(const char* name, const float* valueptr);

	void use();
};


#endif // !SHADERS_H

