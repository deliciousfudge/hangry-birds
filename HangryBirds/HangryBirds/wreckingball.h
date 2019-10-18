//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: wreckingball.h
// Description	: CWreckingBall header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CWreckingBall
{
public:
	CWreckingBall(glm::vec2 _v2PosTether, glm::vec2 _v2SizeTether, glm::vec2 _v2PosBall, glm::vec2 _v2SizeBall, float _fRopeLength);
	~CWreckingBall();

	virtual void Init(b2World& _rWorld);
	virtual void Render(bool _bDebugMode);
	virtual void Update(GLfloat _fDelta);

private:
	b2RopeJointDef* m_pRopeJointDef;
	CEntity* m_pRopeTether;
	CEntity* m_pBall;
	CSprite* m_pRope;

	glm::vec2 m_v2PosTether;
	glm::vec2 m_v2SizeTether;
	glm::vec2 m_v2PosBall;
	glm::vec2 m_v2SizeBall;
	float m_fRopeLength;
};

