//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: wreckingball.cpp
// Description	: Implements a simple wrecking ball using a Box2D rope joint
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes

// This include
#include "wreckingball.h"

// Static Variables

// Static Function Prototypes

// Implementation

CWreckingBall::CWreckingBall(glm::vec2 _v2PosTether, glm::vec2 _v2SizeTether, glm::vec2 _v2PosBall, glm::vec2 _v2SizeBall, float _fRopeLength)
	: m_v2PosTether(_v2PosTether)
	, m_v2SizeTether(_v2SizeTether)
	, m_v2PosBall(_v2PosBall)
	, m_v2SizeBall(_v2SizeBall)
	, m_fRopeLength(_fRopeLength)
{
}

CWreckingBall::~CWreckingBall()
{
	delete m_pRope;
	m_pRope = nullptr;

	delete m_pBall;
	m_pBall = nullptr;

	delete m_pRopeJointDef;
	m_pRopeJointDef = nullptr;

	delete m_pRopeTether;
	m_pRopeTether = nullptr;
}

void CWreckingBall::Init(b2World & _rWorld)
{
	m_pRopeTether = new CEntity(m_v2PosTether, m_v2SizeTether);
	m_pRopeTether->SetSprite(CUtility::GetInstance().ksSpriteWreckingTether.c_str());
	m_pRopeTether->SetPhysicsBody(BODY_STATIC);
	m_pRopeTether->SetPhysicsShape(SHAPE_POLYGON);
	m_pRopeTether->Init(_rWorld);

	m_pBall = new CEntity(m_v2PosBall, m_v2SizeBall);
	m_pBall->SetSprite(CUtility::GetInstance().ksSpriteWreckingBall.c_str());
	m_pBall->SetPhysicsBody(BODY_DYNAMIC);
	m_pBall->SetPhysicsShape(SHAPE_CIRCLE);
	m_pBall->SetDensity(100.0f);
	m_pBall->Init(_rWorld);
	m_pBall->SetScale(glm::vec2(3.5f)); // Increase size of sprite due to food sprites having a larger border

	m_pRopeJointDef = new b2RopeJointDef();
	m_pRopeJointDef->bodyA = m_pRopeTether->GetBody();
	m_pRopeJointDef->bodyB = m_pBall->GetBody();
	m_pRopeJointDef->localAnchorA = b2Vec2(0.0f, 0.0f);
	m_pRopeJointDef->localAnchorB = b2Vec2(0.0f, m_pBall->GetSize().y);
	m_pRopeJointDef->maxLength = m_fRopeLength;

	_rWorld.CreateJoint(m_pRopeJointDef);
}

void CWreckingBall::Render(bool _bDebugMode)
{
	// Only want to see rope tether for debugging purposes
	if (_bDebugMode)
	{
		m_pRopeTether->Render(_bDebugMode);
	}
	
	m_pBall->Render(_bDebugMode);
}

void CWreckingBall::Update(GLfloat _fDelta)
{
	m_pRopeTether->Update(_fDelta);
	m_pBall->Update(_fDelta);
}
