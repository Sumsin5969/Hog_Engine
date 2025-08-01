#include "RenderManager.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <glad/gl.h>
#include <fstream>
#include <sstream>
#include "EngineInternal.h"
#include <vector>
#include <array>

struct RenderManager::Impl
{
	SDL_GLContext glContext;
	SDL_Window* window;
};

GLuint CompileShader(GLenum type, const char* source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader compile error: " << infoLog << std::endl;
	}
	return shader;
}

std::string LoadShaderSource(const char* path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Failed to open shader file: " << path << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint CreateProgram()
{
	std::string vsSource = LoadShaderSource("shaders/myShader.vert");
	std::string fsSource = LoadShaderSource("shaders/myShader.frag");

	GLuint vs = CompileShader(GL_VERTEX_SHADER, vsSource.c_str());
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fsSource.c_str());

	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "Shader Program linking failed: " << infoLog << std::endl;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void RenderManager::Init(SDL_Window* window, int w, int h)
{
	impl = new Impl();
	impl->glContext = SDL_GL_CreateContext(window);
	impl->window = window;
	
	if (!gladLoadGL(SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to init GLAD!!\n";
		return;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	glViewport(0, h/2, w/2, h/2);
	std::vector<HEVec2> vertices = {
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};

	std::array<GLuint, 6> indicies = { 0, 1, 2, 2, 3, 0 };
	
	glCreateVertexArrays(1, &vao);
	glCreateBuffers(1, &vbo);
	glCreateBuffers(1, &ebo);

	glNamedBufferData(vbo, vertices.size() * sizeof(HEVec2), vertices.data(), GL_STATIC_DRAW);
	glNamedBufferData(ebo, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(HEVec2));
	glVertexArrayElementBuffer(vao, ebo);

	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE,0);
	glVertexArrayAttribBinding(vao, 0, 0);
	shaderProgram = CreateProgram();
}

void RenderManager::ClearBackground()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

void RenderManager::Update()
{

}

void RenderManager::Draw()
{
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RenderManager::SwapWindow()
{
	SDL_GL_SwapWindow(impl->window);
}

void RenderManager::Destroy()
{
	if (shaderProgram) glDeleteProgram(shaderProgram);
	if (vao) glDeleteVertexArrays(1, &vao);
	if (vbo) glDeleteBuffers(1, &vbo);
	if (ebo) glDeleteBuffers(1, &ebo);

	SDL_GL_DestroyContext(impl->glContext);
	delete impl;
}