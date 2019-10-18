//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: camera.cpp
// Description	: Singleton that controls camera logic within the game
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "camera.h"
#include "utils.h"

// This include
#include "scenemanager.h"

// Static Variables
CCamera* CCamera::s_pCamera = nullptr;

// Static Function Prototypes

// Implementation

CCamera::CCamera()
	: m_fCameraSpeed(0.25f)
	, m_fPixelToMetre(50.0f)
{
	m_v3CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_v3CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_v3CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	m_m4Projection = glm::ortho(
		-CUtility::GetInstance().fScrWidth / m_fPixelToMetre,
		CUtility::GetInstance().fScrWidth / m_fPixelToMetre,
		-CUtility::GetInstance().fScrHeight / m_fPixelToMetre,
		CUtility::GetInstance().fScrHeight / m_fPixelToMetre,
		-1.0f,
		100.0f
	);
}

CCamera::~CCamera()
{
}

CCamera & CCamera::GetInstance()
{
	if (s_pCamera == nullptr)
	{
		s_pCamera = new CCamera();
	}

	return (*s_pCamera);
}

void CCamera::DestroyInstance()
{
	delete s_pCamera;
	s_pCamera = 0;
}

glm::mat4 CCamera::GetModelMatrix()
{
	return m_m4Model;
}

void CCamera::SetModelMatrix(glm::mat4 _m4Model, GLuint _uiProgram)
{
	m_m4Model = _m4Model;
	m_m4MVP = m_m4Projection * m_m4View * m_m4Model;

	// Pass each new MVP matrix to the shader so that each sprite can have its position updated accordingly
	GLint MVPLoc = glGetUniformLocation(_uiProgram, "MVP");
	glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(m_m4MVP));
}

glm::mat4 CCamera::GetViewMatrix()
{
	return m_m4View;
}

glm::mat4 CCamera::GetProjectionMatrix()
{
	return m_m4Projection;
}

glm::mat4 CCamera::GetMVPMatrix()
{
	return m_m4MVP;
}

float CCamera::GetPixelToMetre() const
{
	return m_fPixelToMetre;
}

void CCamera::Update()
{
	m_m4View = glm::lookAt(
		m_v3CameraPos,							// Camera Position
		m_v3CameraPos + m_v3CameraFront,		// Target Position
		m_v3CameraUp);							// Up Vector

	m_m4MVP = m_m4Projection * m_m4View * m_m4Model;
}