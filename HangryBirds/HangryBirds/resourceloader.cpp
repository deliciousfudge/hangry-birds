//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: resourceloader.cpp
// Description	: Manages shader and texture instances to ensure no duplicate instances are loaded
// Author		: Roger Smith
// Mail			: Roger.Smi7429@mediadesign.school.nz
//

// Library Includes
#include <iostream>
#include <fstream>
#include <vector>

// This Include
#include "resourceloader.h" 

// Static Variables
CResourceLoader* CResourceLoader::s_pShaderLoader = nullptr;

CResourceLoader::CResourceLoader(void){}

CResourceLoader::~CResourceLoader(void)
{
	m_mapShader.clear();
	m_mapTexture.clear();

	delete s_pShaderLoader;
	s_pShaderLoader = nullptr;
}

CResourceLoader& CResourceLoader::GetInstance()
{
	if (s_pShaderLoader == nullptr)
	{
		s_pShaderLoader = new CResourceLoader();
	}

	return (*s_pShaderLoader);
}

void CResourceLoader::DestroyInstance()
{
	delete s_pShaderLoader;
	s_pShaderLoader = nullptr;
}

std::string CResourceLoader::ReadShader(const char* filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()){
		std::cout << "Can't read file " << filename << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint CResourceLoader::CreateShader(GLenum shaderType, std::string
	source, const char* shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);
	const char *shader_code_ptr = source.c_str();
	const int shader_code_size = source.size();

	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	//check for errors
	if (compile_result == GL_FALSE)
	{

		int info_log_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> shader_log(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "ERROR compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}
	return shader;
}

GLuint CResourceLoader::CreateProgram(const char* vertexShaderFilename,
	const char* fragmentShaderFilename)
{
	GLuint vertex_shader;
	GLuint fragment_shader;

	std::string sShaderName = vertexShaderFilename + std::string(fragmentShaderFilename);
	if (m_mapShader.find(sShaderName) == m_mapShader.end())
	{
		//read the shader files and save the code
		std::string vertex_shader_code = ReadShader(vertexShaderFilename);
		std::string fragment_shader_code = ReadShader(fragmentShaderFilename);

		vertex_shader = CreateShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
		fragment_shader = CreateShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

		m_mapShader[vertexShaderFilename] = vertex_shader;
		m_mapShader[fragmentShaderFilename] = fragment_shader;

		int link_result = 0;
		//create the program handle, attach the shaders and link it
		GLuint program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &link_result);
		//check for link errors
		if (link_result == GL_FALSE)
		{

			int info_log_length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
			std::vector<char> program_log(info_log_length);
			glGetProgramInfoLog(program, info_log_length, NULL, &program_log[0]);
			std::cout << "Shader Loader : LINK ERROR" << std::endl << &program_log[0] << std::endl;
			return 0;
		}
		//shader_map[vertexShaderFilename + std::string(fragmentShaderFilename)] = program;
		m_mapShader.insert(std::pair<std::string, GLuint>(sShaderName, program));
		return program;
	}
	else
	{
		return m_mapShader[vertexShaderFilename + std::string(fragmentShaderFilename)];
	}
}

GLuint CResourceLoader::LoadTexture(std::string _sFilename)
{
	if (m_mapTexture.find(_sFilename) == m_mapTexture.end())
	{
		m_mapTexture.insert(std::pair<std::string, GLuint>(_sFilename, 0));
		glGenTextures(1, &m_mapTexture.find(_sFilename)->second);
		glBindTexture(GL_TEXTURE_2D, m_mapTexture.find(_sFilename)->second);

		int width, height;
		unsigned char* image = SOIL_load_image(
			_sFilename.c_str(),
			&width,
			&height,
			0,
			SOIL_LOAD_RGBA
		);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image
		);

		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	return m_mapTexture.find(_sFilename)->second;
}
