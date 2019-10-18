//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: ground.h
// Description	: Ground header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CGround : public CEntity
{
	// Member functions
public:
	CGround(glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX = 1, int _iSpanY = 1, int _iNumSpr = 1);
	~CGround();

	virtual void Init(b2World& _rWorld);
	virtual void Render(bool _bDebugMode);
	virtual void Update(GLfloat _fDelta);
};