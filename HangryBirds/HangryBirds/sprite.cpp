//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: sprite.cpp
// Description	: Initialises, updates, and renders all Sprite objects
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "resourceloader.h"

// This include
#include "sprite.h"

// Static Variables

// Static Function Prototypes

// Implementation

CSprite::CSprite(glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX, int _iSpanY, int _iNumSpr)
	: m_v2Pos(_v2Pos)
	, m_v2StartPos(_v2Pos)
	, m_v2Size(_v2Size)
	, m_v3Rot(glm::vec3(0.0f))
	, m_v2Scale(glm::vec2(1.0f))
	, m_iCurrentSpr(19)
	, m_iSpanX(_iSpanX)
	, m_iSpanY(_iSpanY)
	, m_iNumSpr(_iNumSpr)
{
}

CSprite::~CSprite()
{
}

void CSprite::Init()
{
	m_uiProgram = CResourceLoader::GetInstance().CreateProgram("Resources/Shaders/VertexShader.vs", "Resources/Shaders/FragmentShader.fs");

	float fHalfWidth = m_v2Size.x / 2.0f;
	float fHalfHeight = m_v2Size.y / 2.0f;
	
	GLfloat vertices[] = {
		// Positions						// Colors			// Tex Coords
		-fHalfWidth, fHalfHeight, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// Top Left
		fHalfWidth, fHalfHeight, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// Top Right
		fHalfWidth, -fHalfHeight, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,		// Bottom Right
		-fHalfWidth, -fHalfHeight, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		// Bottom Left
	};

	GLuint indices[] = {
		0, 1, 2,	// First Triangle
		0, 2, 3,	// Second Triangle
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW);

	glGenTextures(1, &m_uiTexture);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);

	LoadTexture(m_kcpFilename);
}

void CSprite::Render()
{
	glDisable(GL_DEPTH_TEST);
	glm::vec3 objPosition = glm::vec3(m_v2Pos, 0.0f);
	glm::vec3 objScale = glm::vec3(m_v2Scale, 1.0f);

	glm::mat4 m_m4Translate = glm::translate(glm::mat4(), objPosition);
	glm::mat4 m_m4Scale = glm::scale(glm::mat4(), objScale);
	glm::mat4 m_m4Rotate = glm::rotate(glm::mat4(), m_v3Rot.x, glm::vec3(1, 0, 0));
	m_m4Rotate = glm::rotate(m_m4Rotate, m_v3Rot.y, glm::vec3(0, 1, 0));
	m_m4Rotate = glm::rotate(m_m4Rotate, m_v3Rot.z, glm::vec3(0, 0, 1));
	
	// Model matrix to store transformations
	glm::mat4 m_m4Model = m_m4Translate * m_m4Rotate * m_m4Scale;

	glUseProgram(m_uiProgram);
	CCamera::GetInstance().SetModelMatrix(m_m4Model, m_uiProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_uiTexture);
	glUniform1i(glGetUniformLocation(m_uiProgram, "tex"), 0);

	glBindVertexArray(VAO);		// Bind VAO

	m_fTexHeight = 1.0f / static_cast<float>(m_iSpanY);
	GLint iTexHeightLoc = glGetUniformLocation(m_uiProgram, "TexHeight");
	glUniform1f(iTexHeightLoc, m_fTexHeight);

	m_fTexWidth = 1.0f / static_cast<float>(m_iSpanX);
	GLint iTexWidthLoc = glGetUniformLocation(m_uiProgram, "TexWidth");
	glUniform1f(iTexWidthLoc, m_fTexWidth);

	m_fXOffset = (0.0f + (static_cast<float>(m_iCurrentSpr % m_iSpanX)) * m_fTexWidth);
	GLint xOffsetLoc = glGetUniformLocation(m_uiProgram, "xOffset");
	glUniform1f(xOffsetLoc, m_fXOffset);

	m_fYOffset = (0.0f + (static_cast<float>(m_iCurrentSpr / m_iSpanX)) * m_fTexHeight);
	GLint iYOffsetLoc = glGetUniformLocation(m_uiProgram, "yOffset");
	glUniform1f(iYOffsetLoc, m_fYOffset);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void CSprite::Update(GLfloat _fDelta)
{
	m_fLeft = m_v2Pos.x - (m_v2Size.x / 2.0f);
	m_fRight = m_v2Pos.x + (m_v2Size.x / 2.0f);
}

void CSprite::MoveSprite(float _fTranslateX, float _fTranslateY)
{
	m_v2OldPos = m_v2Pos;
	m_v2Pos.x += _fTranslateX;
	m_v2Pos.y += _fTranslateY;
}

void CSprite::LoadTexture(const char* _kcpFilename)
{
	int width, height;
	unsigned char* image = SOIL_load_image(
		_kcpFilename,
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int CSprite::GetCurrentSprite() const
{
	return m_iCurrentSpr;
}

void CSprite::SetCurrentSprite(int _iSpr)
{
	m_iCurrentSpr = _iSpr;
}

int CSprite::GetSpanX() const
{
	return m_iSpanX;
}

void CSprite::SetSpanX(int _iSpanX)
{
	m_iSpanX = _iSpanX;
}

int CSprite::GetSpanY() const
{
	return m_iSpanY;
}

void CSprite::SetSpanY(int _iSpanY)
{
	m_iSpanY = _iSpanY;
}

glm::vec2 CSprite::GetPos() const
{
	return m_v2Pos;
}

void CSprite::SetPos(glm::vec2 _v2Pos)
{
	m_v2Pos = _v2Pos;
}

glm::vec2 CSprite::GetScale() const
{
	return m_v2Scale;
}

void CSprite::SetScale(glm::vec2 _v2Scale)
{
	m_v2Scale = _v2Scale;
}

glm::vec3 CSprite::GetRot() const
{
	return m_v3Rot;
}

void CSprite::SetRot(glm::vec3 _v3Rot)
{
	m_v3Rot = _v3Rot;
}

glm::vec2 CSprite::GetSize()
{
	return m_v2Size;
}

void CSprite::SetSprite(const char* _kcpFilename)
{
	m_kcpFilename = _kcpFilename;
}

float CSprite::GetLeft()
{
	return m_fLeft;
}

float CSprite::GetRight()
{
	return m_fRight;
}
