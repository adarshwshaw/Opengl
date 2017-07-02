#include<iostream>
#include<GL\glew.h>
#include <GLFW\glfw3.h>
#include"shader\shader.h"
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include"stb_image.h"
#define Log(x) std::cout << x << std::endl



int main(int argc, char* argv[]){
	if (!glfwInit())
		Log("Error in initialization!!");
	GLFWwindow *window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
	if (!window){
		glfwTerminate();
		Log("Window creation error");
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	if (glewInit() != GLEW_OK){
		glfwDestroyWindow(window);
		glfwTerminate();
		Log("Glew init error!");
		system("pause");
		return -1;
	}

	GLfloat vert[] = {
		-0.5f, -0.5f, 0,
		-0.5f,  0.5f, 0,
		 0.5f,  0.5f, 0,
		 0.5f,  0.5f, 0,
		 0.5f, -0.5f, 0,
		-0.5f, -0.5f, 0,
	};

	GLfloat texc[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
	};

	int w, h, nc;
	unsigned char* tex=stbi_load("img.png", &w, &h, &nc, 4);
	GLuint m_texId;
	glGenTextures(1, &m_texId);
	glBindTexture(GL_TEXTURE_2D, m_texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	stbi_image_free(tex);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	GLuint tbo;
	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texc),texc, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);

	Shader s("shader/basic");
	s.bind();
	glBindTexture(GL_TEXTURE_2D, m_texId);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(-0.4f, 0, 0))*glm::rotate(glm::mat4(1.0f),3.14f/2.0f,glm::vec3(0.0f,0.0f,1.0f));
	
	glUniformMatrix4fv(glGetUniformLocation(s.m_program, "trans"), 1, GL_FALSE, &trans[0][0]);

	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		///
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		///
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
	s.unbind();
	glDeleteTextures(1, &m_texId);
	glfwDestroyWindow(window);
	window = NULL;
	glfwTerminate();
	//system("pause");
	return 0;
}