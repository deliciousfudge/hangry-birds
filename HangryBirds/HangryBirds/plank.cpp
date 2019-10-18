//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: plank.cpp
// Description	: Derivation of entity class that controls plank logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "plank.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlank::CPlank(glm::vec2 _v2Pos, glm::vec2 _v2Size, bool _bBreakable, int _iSpanX, int _iSpanY, int _iNumSpr)
	: CEntity(_v2Pos, _v2Size, _iSpanX, _iSpanY, _iNumSpr)
	, m_bBreakable(_bBreakable)
{
}

CPlank::~CPlank()
{
}

void CPlank::Init(b2World & _rWorld)
{
	m_ePhysicsBody = BODY_DYNAMIC;

	if (m_bBreakable)
	{
		m_kcpFilename = CUtility::GetInstance().ksSpritePlankBreakable.c_str();
		m_eEntityType = ENTITY_BPLANK;
		m_fHealth = CUtility::GetInstance().kfHealthBreakablePlank;
	}
	else
	{
		m_kcpFilename = CUtility::GetInstance().ksSpritePlankUnbreakable.c_str();
		m_eEntityType = ENTITY_PLANK;
	}

	CEntity::Init(_rWorld);
}

void CPlank::Render(bool _bDebugMode)
{
	CEntity::Render(_bDebugMode);
}

void CPlank::Update(GLfloat _fDelta)
{
	CEntity::Update(_fDelta);
}
