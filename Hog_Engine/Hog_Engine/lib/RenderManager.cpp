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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <cmath>

struct RenderManager::Impl
{
	SDL_GLContext glContext;
	SDL_Window* window;
};
struct Vertex
{
	glm::vec2 pos;
	glm::vec2 tex;
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

void RenderManager::Init(SDL_Window* window, float w, float h)
{
	impl = new Impl();
	impl->glContext = SDL_GL_CreateContext(window);
	impl->window = window;
	screenWidth = w;
	screenHeight = h;
	if (!gladLoadGL(SDL_GL_GetProcAddress))
	{
		std::cerr << "Failed to init GLAD!!\n";
		return;
	}
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glViewport(0, 0, w, h);

	shaderProgram = CreateProgram();
}

void RenderManager::ClearBackground(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void RenderManager::LoadTexture(const char* path)
{
	GLuint texture;
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (!data)
	{
		std::cerr << "Failed to load texture\n";
		return;
	}

	GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB;
	GLenum internalFormat = nrChannels == 4 ? GL_RGBA8 : GL_RGB8;

	glTextureStorage2D(texture, 1, internalFormat, width, height);
	glTextureSubImage2D(texture, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	std::vector<Vertex> vertices = {
		{ { 0.5f,  0.5f}, {1.f, 1.f} },
		{ { 0.5f, -0.5f}, {1.f, 0.f} },
		{ {-0.5f, -0.5f}, {0.f, 0.f} },
		{ {-0.5f,  0.5f}, {0.f, 1.f} }
	};
	std::array<GLuint, 6> indices = { 0, 1, 2, 2, 3, 0 };

	GLuint vbo, ebo;
	glCreateVertexArrays(1, &vao);
	glCreateBuffers(1, &vbo);
	glCreateBuffers(1, &ebo);

	glNamedBufferData(vbo, vertices.size() * sizeof(Vertex),
		vertices.data(), GL_DYNAMIC_DRAW);
	glNamedBufferData(ebo, indices.size() * sizeof(GLuint),
		indices.data(), GL_DYNAMIC_DRAW);

	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(Vertex));
	glVertexArrayElementBuffer(vao, ebo);

	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
	glVertexArrayAttribBinding(vao, 0, 0);

	glEnableVertexArrayAttrib(vao, 2);
	glVertexArrayAttribFormat(vao, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, tex));
	glVertexArrayAttribBinding(vao, 2, 0);

	GLint textureLocation = glGetUniformLocation(shaderProgram, "uTexture");
	glUniform1i(textureLocation, 0);

	glBindTextureUnit(0, texture);
	glGenerateTextureMipmap(texture);
}

void RenderManager::Update()
{
	
}

void RenderManager::Draw()
{
	static GLfloat x, y, w, h;
	x = 100;
	y = 0;
	w = 1100;
	h = 1466;
	glm::mat4 model_to_ndc(1.f);
	
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(w, h, 1));
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 1));
	glm::mat4 ortho = glm::ortho(-screenWidth/2.f, screenWidth/2.f, -screenHeight/2.f, screenHeight/2.f);
	model_to_ndc =  ortho * translate * scale;
	GLint trans = glGetUniformLocation(shaderProgram, "uModel_to_NDC");
	GLint color = glGetUniformLocation(shaderProgram, "uColor");
	glm::vec4 clr = {1,1,1,1};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(trans, 1, GL_FALSE, &model_to_ndc[0][0]);
	glUniform4fv(color, 1, &clr[0]);
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