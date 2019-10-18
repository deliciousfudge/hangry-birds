//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: plank.h
// Description	: CPlank header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes
#include "entity.h"

// Types
struct PlankAttrib
{
	glm::vec2 v2Pos;
	glm::vec2 v2Size;
	float fRot;
	bool bBreakable;

	// Overload constructor
	PlankAttrib(glm::vec2 _v2Pos = glm::vec2(0.0f), float _fRot = 0.0f, glm::vec2 _v2Size = glm::vec2(0.5f, 0.25f), bool _bBreakable = false)
		: v2Pos(_v2Pos)
		, fRot(_fRot)
		, v2Size(_v2Size)
		, bBreakable(_bBreakable)
	{

	}
};

// Constants

// Prototypes

class CPlank : public CEntity
{
	// Member functions
public:
	CPlank(glm::vec2 _v2Pos, glm::vec2 _v2Size, bool _bBreakable, int _iSpanX = 1, int _iSpanY = 1, int _iNumSpr = 1);
	~CPlank();

	virtual void Init(b2World& _rWorld);
	virtual void Render(bool _bDebugMode);
	virtual void Update(GLfloat _fDelta);

private:
	bool m_bBreakable;
};