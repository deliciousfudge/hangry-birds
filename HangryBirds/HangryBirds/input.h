//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: input.h
// Description	: CInput header file
// Author		: Roger Smith
// Mail			: Roger.Smi7429@mediadesign.school.nz
//

#pragma once

#ifndef __INPUT_H__
#define __INPUT_H__

// Library Includes
#include <glew.h>
#include <freeglut.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <string>
#include <strstream>
#include <sstream>

// Local Includes
#include "entity.h"
#include "utils.h"
#include "TextLabel.h"

// Types
enum InputState
{
	INPUT_FIRST_RELEASE,
	INPUT_RELEASED,
	INPUT_FIRST_PRESS,
	INPUT_HOLD,
};

enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};

// Handy String Conversions
template<typename T>
std::string ConvertToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
};

// Prototypes
class CEntity;

class CInput
{
	// Member methods
public:
	~CInput();

	// Singleton Methods
	static CInput& GetInstance();
	static void DestroyInstance();

	void KeyBoardDown(unsigned char _ucKey, int _iX, int _iY);
	void KeyBoardUp(unsigned char _ucKey, int _iX, int _iY);
	void Mouse(int _iButton, int _iGlutState, int _iX, int _iY);
	void MousePassiveMovement(int _iX, int _iY);
	unsigned char GetKeyState(unsigned char _ucKey);
	unsigned char GetMouseState(int _iButton);

	glm::vec3 GetRotAngle() const;
	void SetRotAngle(glm::vec3 _v3RotAngle);

	glm::vec2 GetMousePos() const;

	void Update();

private:
	CInput();

	// Member variables
protected:
	static CInput* s_pInput;

private:
	unsigned char m_ucKeyState[255];
	unsigned char m_ucMouseState[3];
	GLfloat m_fMouseSensitivity;
	glm::vec3 m_v3RotAngle;
	GLfloat m_fYaw;
	GLfloat m_fPitch;
	GLfloat m_fLastX;
	GLfloat m_fLastY;
	bool m_bFirstMouse;
	glm::vec3 m_v3RayDirection;
	glm::vec2 m_v2MousePos;
};

#endif __INPUT_H__
