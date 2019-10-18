//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: bird.cpp
// Description	: Derivation of entity class that controls bird logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "bird.h"

// Static Variables

// Static Function Prototypes

// Implementation

CBird::CBird(glm::vec2 _v2Pos, glm::vec2 _v2Size, EBirdType _eBirdType, int _iSpanX, int _iSpanY, int _iNumSpr)
	: CEntity(_v2Pos, _v2Size, _iSpanX, _iSpanY, _iNumSpr)
	, m_eBirdType(_eBirdType)
{
	
}

CBird::~CBird()
{

}

void CBird::Init(b2World& _rWorld)
{
	m_eEntityType = ENTITY_BIRD;
	m_fHealth = CUtility::GetInstance().kfHealthBird;

	m_ePhysicsBody = BODY_DYNAMIC;
	m_ePhysicsShape = SHAPE_CIRCLE;
	SetFriction(1.0f);
	SetLinearDamping(0.03f);
	m_fRestitution = 1.0f;
	m_fDensity = 1.0f;

	CEntity::Init(_rWorld);

	m_pUserData->m_eEntityType = m_eEntityType;
	m_pUserData->m_eBirdType = m_eBirdType;
}

void CBird::Render(bool _bDebugMode)
{
	CEntity::Render(_bDebugMode);
}

void CBird::Update(GLfloat _fDelta)
{
	CEntity::Update(_fDelta);
}

bool CBird::GetIsActive() const
{
	return m_bIsActive;
}

void CBird::SetIsActive(bool _bIsActive)
{
	m_bIsActive = _bIsActive;
}

EBirdType& CBird::GetType() const
{
	return m_pUserData->m_eBirdType;
}

void CBird::SetType(EBirdType _eType)
{
	m_pUserData->m_eBirdType = _eType;
}
