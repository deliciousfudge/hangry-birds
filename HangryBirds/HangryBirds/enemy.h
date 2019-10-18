//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School.
//
// File Name	: enemy.h
// Description	: CEnemy header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes
#include "entity.h"

// Types
enum EEnemyType
{
	ENEMY_LURKER = 0,
	ENEMY_SHOOTER = 1,
	ENEMY_BOUNCER = 2
};

// Constants

// Prototypes


class CEnemy: public CEntity
{
	// Member functions
public:
	CEnemy(GLuint _uiEnemyType, glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX = 1, int _iSpanY = 1, int _iNumSpr = 1);
	~CEnemy();

	virtual void Init(b2World& _rWorld);
	virtual void Render(bool _bDebugMode);
	virtual void Update(GLfloat _fDelta);

	// Member variables
private:
	bool m_bIsShooting;
	GLuint m_uiEnemyType{ 0 };

	std::string m_sSpriteFilename = CUtility::GetInstance().ksSpriteEnemy0;
};
