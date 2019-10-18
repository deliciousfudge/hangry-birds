//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: seesaw.h
// Description	: CSeesaw header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CSeesaw
{
public:
	CSeesaw(glm::vec2 _v2Pos, glm::vec2 _v2Size);
	~CSeesaw();

	virtual void Init(b2World& _rWorld);
	virtual void Render(bool _bDebugMode);
	virtual void Update(GLfloat _fDelta);

private:
	CEntity* m_pBase;
	CEntity* m_pBoard;

	b2RevoluteJointDef* m_pRevoluteJointDef;

	glm::vec2 m_v2Pos;
	glm::vec2 m_v2Size;
};

