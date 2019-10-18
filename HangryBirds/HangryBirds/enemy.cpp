//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: enemy.cpp
// Description	: Controls enemy implementation logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "enemy.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEnemy::CEnemy(GLuint _uiEnemyType, glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX, int _iSpanY, int _iNumSpr)
	: CEntity(_v2Pos, _v2Size, _iSpanX, _iSpanY, _iNumSpr)
	, m_uiEnemyType(_uiEnemyType)
{

}

CEnemy::~CEnemy()
{
}

void CEnemy::Init(b2World& _rWorld)
{
	m_ePhysicsBody = BODY_DYNAMIC;
	m_ePhysicsShape = SHAPE_CIRCLE;
	m_fHealth = CUtility::GetInstance().kfHealthEnemy;
	m_eEntityType = ENTITY_ENEMY;

	switch (m_uiEnemyType)
	{
	case 0:
	{
		m_kcpFilename = CUtility::GetInstance().ksSpriteEnemy0.c_str();
	}
	break;

	case 1:
	{
		m_kcpFilename = CUtility::GetInstance().ksSpriteEnemy1.c_str();
	}
	break;

	case 2:
	{
		m_kcpFilename = CUtility::GetInstance().ksSpriteEnemy2.c_str();
	}
	break;
	default:break;
	}

	CEntity::Init(_rWorld);
	SetScale(glm::vec2(3.0f));
}

void CEnemy::Render(bool _bDebugMode)
{
	CEntity::Render(_bDebugMode);
}

void CEnemy::Update(GLfloat _fDelta)
{
	CEntity::Update(_fDelta);
}
