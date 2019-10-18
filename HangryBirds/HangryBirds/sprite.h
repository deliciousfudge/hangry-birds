//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: sprite.h
// Description	: CSprite header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <soil\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

// Local Includes
#include "resourceloader.h"
#include "camera.h"
#include "utils.h"

// Types

// Constants

// Prototypes

class CSprite
{
	// Member functions
public:
	CSprite(glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX = 1, int _iSpanY = 1, int _iNumSpr = 1);
	~CSprite();

	void Init();
	void Render();
	void Update(GLfloat _fDelta);
	void MoveSprite(float _fTranslateX, float _fTranslateY);
	void LoadTexture(const char* _kcpFilename);

	int GetCurrentSprite() const;
	void SetCurrentSprite(int _iSpr);

	int GetSpanX() const;
	void SetSpanX(int _iSpanX);

	int GetSpanY() const;
	void SetSpanY(int _iSpanY);

	glm::vec2 GetPos() const;
	void SetPos(glm::vec2 _v2Pos);

	glm::vec2 GetScale() const;
	void SetScale(glm::vec2 _v2Scale);

	glm::vec3 GetRot() const;
	void SetRot(glm::vec3 _v3Rot);

	glm::vec2 GetSize();

	void SetSprite(const char* _kcpFilename);

	float GetLeft();
	float GetRight();

	// Member variables
protected:
	glm::vec2 m_v2Pos;
	glm::vec2 m_v2OldPos;
	glm::vec2 m_v2StartPos;
	glm::vec2 m_v2Size;
	glm::vec3 m_v3Rot;
	glm::vec2 m_v2Scale;

	GLuint m_uiTexture;
	GLuint m_uiProgram;

	int m_iCurrentSpr;
	int m_iSpanX;
	int m_iSpanY;
	int m_iNumSpr;

	float m_fLeft;
	float m_fRight;

	const char* m_kcpFilename;

private:
	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	GLfloat m_fTexHeight;
	GLfloat m_fTexWidth;
	GLfloat m_fXOffset = 0.0f;
	GLfloat m_fYOffset = 0.0f;
};

