//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: textlabel.h
// Description	: TextLabel header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include <map>
#include <string>
#include <iostream>

// Local Includes
#include "resourceloader.h"
#include "Utils.h"

// Types
struct Character
{
	GLuint      TextureID;	// Texture ID 
	glm::ivec2  Size;	// Size of glyph
	glm::ivec2  Bearing;	// Positon of glyph 
	GLuint      Advance;	// How far to move for the next character
};

// Constants

// Prototypes

class TextLabel {
public:
	TextLabel(std::string text, std::string font, glm::vec2 pos);
	~TextLabel();

	void Render();
	void SetText(std::string newText) { text = newText; };
	void SetColor(glm::vec3 newColor) { color = newColor; };
	void SetScale(GLfloat newScale) { scale = newScale; };
	void SetPosition(glm::vec2 newPosition) { position = newPosition; };

private:
	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;

	GLuint VAO, VBO, program;
	std::map<GLchar, Character> Characters;
};