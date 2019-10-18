//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: input.cpp
// Description	: Singleton that controls input logic
// Author		: Roger Smith
// Mail			: Roger.Smi7429@mediadesign.school.nz
//

// Local Includes
#include "camera.h"

// This Include
#include "input.h"

// Static Variables
CInput* CInput::s_pInput = nullptr;

CInput::CInput()
	: m_fMouseSensitivity(CUtility::GetInstance().kfMouseSensitivity)
	, m_v3RotAngle(glm::vec3(0.0f))
	, m_fLastX(CUtility::GetInstance().fScrWidth * 0.5f)
	, m_fLastY(CUtility::GetInstance().fScrHeight * 0.5f)
	, m_fPitch(0.0f) 	// Set the pitch of the camera to match the user defined pitch
	, m_bFirstMouse(true)
{
	for (int i = 0; i < 255; i++)
	{
		m_ucKeyState[i] = INPUT_RELEASED;
	}

	for (int i = 0; i < 3; ++i)
	{
		m_ucMouseState[i] = INPUT_RELEASED;
	}
}

CInput::~CInput()
{
}

CInput& CInput::GetInstance()
{
	if (s_pInput == nullptr)
	{
		s_pInput = new CInput();
	}

	return (*s_pInput);

}

void CInput::DestroyInstance()
{
	delete s_pInput;
	s_pInput = 0;
}

void CInput::KeyBoardDown(unsigned char _ucKey, int _iX, int _iY)
{
	m_ucKeyState[_ucKey] = INPUT_FIRST_PRESS;
}

void CInput::KeyBoardUp(unsigned char _ucKey, int _iX, int _iY)
{
	m_ucKeyState[_ucKey] = INPUT_FIRST_RELEASE;
}

void CInput::Mouse(int _iButton, int _iGlutState, int _iX, int _iY)
{
	if (_iButton < 3)
	{
		m_ucMouseState[_iButton] = (_iGlutState == GLUT_DOWN) ? INPUT_FIRST_PRESS : INPUT_FIRST_RELEASE;
	}
}

void CInput::MousePassiveMovement(int _iX, int _iY)
{
	// If this is the first movement of the mouse in the game
	if (m_bFirstMouse)
	{
		// Set the position of the mouse to match the first hovered-over position
		m_fLastX = static_cast<float>(_iX);
		m_fLastY = static_cast<float>(_iY);
		m_bFirstMouse = false;
	}

	m_v2MousePos.x = (2.0f * static_cast<float>(_iX)) / CUtility::GetInstance().fScrWidth - 1.0f;
	m_v2MousePos.y = 1.0f - (2.0f * static_cast<float>(_iY)) / CUtility::GetInstance().fScrHeight;

	// Calculate the difference in mouse movement since the last mouse position update
	GLfloat fXOffset = _iX - m_fLastX;
	GLfloat fYOffset = _iY - m_fLastY;
	m_fLastX = static_cast<float>(_iX);
	m_fLastY = static_cast<float>(_iY);

	// Multiply the X offset by the mouse sensitivity to slow down or speed up the rate of movement accordingly
	fXOffset *= m_fMouseSensitivity;
	fYOffset *= m_fMouseSensitivity;
}
	
unsigned char CInput::GetKeyState(unsigned char _ucKey)
{
	return m_ucKeyState[_ucKey];
}

unsigned char CInput::GetMouseState(int _iButton)
{
	return m_ucMouseState[_iButton];
}

glm::vec3 CInput::GetRotAngle() const
{
	return m_v3RotAngle;
}

void CInput::SetRotAngle(glm::vec3 _v3RotAngle)
{
	m_v3RotAngle = _v3RotAngle;
}

glm::vec2 CInput::GetMousePos() const
{
	return m_v2MousePos;
}

void CInput::Update()
{
	for (int i = 0; i < 255; i++)
	{
		if (CInput::GetInstance().GetKeyState(i) == INPUT_FIRST_PRESS)
		{
			m_ucKeyState[i] = INPUT_HOLD;
		}
		else if (CInput::GetInstance().GetKeyState(i) == INPUT_FIRST_RELEASE)
		{
			m_ucKeyState[i] = INPUT_RELEASED;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		if (m_ucMouseState[i] == INPUT_FIRST_PRESS)
		{
			m_ucMouseState[i] = INPUT_HOLD;
		}
		else if (m_ucMouseState[i] == INPUT_FIRST_RELEASE)
		{
			m_ucMouseState[i] = INPUT_RELEASED;
		}
	}
}
