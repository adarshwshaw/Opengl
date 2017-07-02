#pragma once
#include<gl\glew.h>
#include<string>
class Shader{
private:
	std::string m_file;
	GLuint load();
public:
	GLuint m_program;
	Shader(std::string file);
	~Shader(){ glDeleteProgram(m_program); }
	std::string read_file(std::string path);
	void bind();
	void unbind();
};