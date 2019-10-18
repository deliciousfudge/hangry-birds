//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: resourceloader.h
// Description	: CResourceLoader header file
// Author		: Roger Smith
// Mail			: Roger.Smi7429@mediadesign.school.nz
//

#pragma once

// Library Includes
#include <SOIL.h>
#include <iostream>
#include <map>

// Local Includes
#include "glew.h"
#include "freeglut.h"

class CResourceLoader
{
	// Member methods
public:
	~CResourceLoader(void);

	static CResourceLoader& GetInstance();
	static void DestroyInstance();

	GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);
	GLuint LoadTexture(std::string _sFilename);

private:
	CResourceLoader(void);
	std::string ReadShader(const char* filename);
	GLuint CreateShader(GLenum shaderType, std::string source, const char* shaderName);

	// Member variables
protected:
	static CResourceLoader* s_pShaderLoader;

private:
	std::map<std::string, GLuint> m_mapShader;
	std::map<std::string, GLuint> m_mapTexture;
};
