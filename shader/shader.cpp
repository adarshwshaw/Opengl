#include"shader.h"
#include<fstream>
#include<iostream>

Shader::Shader(std::string file) :m_file(file){

	m_program = load();

}

std::string Shader::read_file(std::string path){
	std::ifstream infile;
	infile.open(path);
	infile.seekg(0, std::ios::end);
	unsigned int lenght = infile.tellg();
	infile.seekg(0, std::ios::beg);
	char *data = new char[lenght + 1];
	memset(data, 0, lenght + 1);
	infile.read(data, lenght);
	infile.close();
	return std::string(data);
}

GLuint Shader::load(){
	GLuint program=glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vstr = read_file(m_file + ".ver");
	std::string fstr = read_file(m_file + ".fra");

	const char* vertsrc = vstr.c_str();
	const char* fragsrc = fstr.c_str();

	
	glShaderSource(vertex, 1, &vertsrc, NULL);
	glCompileShader(vertex);

	GLint res;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		std::cout << "ver error\n";
		return 0;
	}

	glShaderSource(fragment, 1, &fragsrc, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		std::cout << "fra error\n";
		return 0;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

void Shader::bind(){
	glUseProgram(m_program);
}
void Shader::unbind(){
	glUseProgram(m_program);
}