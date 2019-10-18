//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: ground.cpp
// Description	: Derivation of entity class that controls ground logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes

// This include
#include "ground.h"

// Static Variables

// Static Function Prototypes

// Implementation

CGround::CGround(glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX, int _iSpanY, int _iNumSpr)
	: CEntity(_v2Pos, _v2Size, _iSpanX, _iSpanY, _iNumSpr)
{
}

CGround::~CGround()
{
}

void CGround::Init(b2World& _rWorld)
{
	SetFriction(1.0f);
	SetRestitution(0.8f);
	m_eEntityType = ENTITY_GROUND;
	CEntity::Init(_rWorld);
}

void CGround::Render(bool _bDebugMode)
{
	CEntity::Render(_bDebugMode);
}

void CGround::Update(GLfloat _fDelta)
{
	CEntity::Update(_fDelta);
}
