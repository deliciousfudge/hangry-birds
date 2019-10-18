//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: camera.h
// Description	: CCamera header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glew\glew.h>

// Local Includes

// Types

// Constants

// Prototypes

class CCamera
{
	// Member functions
public:
	~CCamera();

	static CCamera& GetInstance();
	static void DestroyInstance();

	glm::mat4 GetModelMatrix();
	void SetModelMatrix(glm::mat4 _m4Model, GLuint _uiProgram);

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix();

	glm::mat4 GetMVPMatrix();

	float GetPixelToMetre() const;

	void Update();

private:
	CCamera();

	// Member variables
protected:
	static CCamera* s_pCamera;

private:

	glm::mat4 m_m4Projection;
	glm::mat4 m_m4View;
	glm::mat4 m_m4Model;
	glm::mat4 m_m4MVP;

	glm::vec3 m_v3CameraPos;
	glm::vec3 m_v3CameraFront;
	glm::vec3 m_v3CameraUp;
	float m_fCameraSpeed;

	float m_fPixelToMetre;
};