//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: seesaw.cpp
// Description	: Implements a simple seesaw using a Box2D revolute joint
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes

// This include
#include "seesaw.h"

// Static Variables

// Static Function Prototypes

// Implementation

CSeesaw::CSeesaw(glm::vec2 _v2Pos, glm::vec2 _v2Size)
	: m_v2Pos(_v2Pos)
	, m_v2Size(_v2Size)
{
}

CSeesaw::~CSeesaw()
{
	delete m_pBase;
	m_pBase = nullptr;

	delete m_pBoard;
	m_pBoard = nullptr;

	delete m_pRevoluteJointDef;
	m_pRevoluteJointDef = nullptr;
}

void CSeesaw::Init(b2World & _rWorld)
{
	// Set up the base (triangle piece) of the seesaw
	m_pBase = new CEntity(m_v2Pos, m_v2Size);
	m_pBase->SetSprite(CUtility::GetInstance().ksSpriteSeesawBase.c_str());
	m_pBase->SetPhysicsShape(SHAPE_TRIANGLE);
	m_pBase->SetPhysicsBody(BODY_STATIC);
	m_pBase->SetDensity(1.0f);
	m_pBase->Init(_rWorld);
	m_pBase->SetScale(glm::vec2(4.0f));

	// Set up the board (top piece) of the seesaw
	m_pBoard = new CEntity(glm::vec2(m_v2Pos.x, m_v2Pos.y), glm::vec2(m_v2Size.x * 4.0f, m_v2Size.y / 2.0f));
	m_pBoard->SetSprite(CUtility::GetInstance().ksSpriteSeesawBoard.c_str());
	m_pBoard->SetPhysicsShape(SHAPE_POLYGON);
	m_pBoard->SetPhysicsBody(BODY_DYNAMIC);
	m_pBoard->SetDensity(0.1f);
	m_pBoard->SetRestitution(0.3f);
	m_pBoard->Init(_rWorld);

	// Create a revolute (rotation only) joint and pin the two pieces together
	m_pRevoluteJointDef = new b2RevoluteJointDef();
	m_pRevoluteJointDef->bodyA = m_pBase->GetBody();
	m_pRevoluteJointDef->bodyB = m_pBoard->GetBody();
	m_pRevoluteJointDef->localAnchorA = b2Vec2(0.0f, 1.0f);
	m_pRevoluteJointDef->localAnchorB = b2Vec2(0.0f, 0.0f);
	m_pRevoluteJointDef->lowerAngle = glm::radians(-60.0f);
	m_pRevoluteJointDef->upperAngle = glm::radians(60.0f);
	_rWorld.CreateJoint(m_pRevoluteJointDef);
}

void CSeesaw::Render(bool _bDebugMode)
{
	m_pBoard->Render(_bDebugMode);
	m_pBase->Render(_bDebugMode);
}

void CSeesaw::Update(GLfloat _fDelta)
{
	m_pBase->Update(_fDelta);
	m_pBoard->Update(_fDelta);
}
