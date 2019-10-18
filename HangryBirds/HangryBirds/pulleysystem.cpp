//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: pulleysystem.cpp
// Description	: Derivation of entity class that implements a simple pulley system
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes

// This include
#include "pulleysystem.h"

// Static Variables

// Static Function Prototypes

// Implementation
CPulleySystem::CPulleySystem(glm::vec2 _v2Gear1Pos, glm::vec2 _v2Gear1Size, glm::vec2 _v2Gear2Pos, glm::vec2 _v2Gear2Size)
	: m_v2Gear1Pos(_v2Gear1Pos)
	, m_v2Gear1Size(_v2Gear1Size)
	, m_v2Gear2Pos(_v2Gear2Pos)
	, m_v2Gear2Size(_v2Gear2Size)
{
}


CPulleySystem::~CPulleySystem()
{
	delete m_pGear1;
	m_pGear1 = nullptr;

	delete m_pGear2;
	m_pGear2 = nullptr;

	delete m_pWeight;
	m_pWeight = nullptr;

	delete m_pTarget;
	m_pTarget = nullptr;

	delete m_pPulleyJointDef;
	m_pPulleyJointDef = nullptr;
}

void CPulleySystem::Init(b2World & _rWorld)
{
	m_pWorld = &_rWorld;

	// Set up the two gears (pieces that the pulley ropes will clamp to)
	m_pGear1 = new CEntity(m_v2Gear1Pos, m_v2Gear1Size);
	m_pGear1->SetPhysicsShape(SHAPE_CIRCLE);
	m_pGear1->SetSprite(CUtility::GetInstance().ksSpritePulleyGear.c_str());
	m_pGear1->Init(_rWorld);

	m_pGear2 = new CEntity(m_v2Gear2Pos, m_v2Gear2Size);
	m_pGear2->SetPhysicsShape(SHAPE_CIRCLE);
	m_pGear2->SetSprite(CUtility::GetInstance().ksSpritePulleyGear.c_str());
	m_pGear2->Init(_rWorld);

	// Set up the weight (large red sphere) on the right hand side of the pulley
	m_pWeight = new CEntity(glm::vec2(m_v2Gear2Pos.x, m_v2Gear2Pos.y - 2.0f), glm::vec2(1.5f));
	m_pWeight->SetPhysicsShape(SHAPE_CIRCLE);
	m_pWeight->SetPhysicsBody(BODY_DYNAMIC);
	m_pWeight->SetEntityType(ENTITY_WEIGHT);
	m_pWeight->SetDensity(20.0f);
	m_pWeight->SetRestitution(1.0f);
	m_pWeight->SetSprite(CUtility::GetInstance().ksSpritePulleyWeight.c_str());
	m_pWeight->Init(_rWorld);
	m_pWeight->SetScale(glm::vec2(4.0f));

	// Set up the target on the left hand side of the pulley
	m_pTarget = new CEntity(glm::vec2(m_v2Gear1Pos.x, m_v2Gear1Pos.y - 2.0f), glm::vec2(1.0f));
	m_pTarget->SetSprite(CUtility::GetInstance().ksSpritePulleyTarget.c_str());
	m_pTarget->SetPhysicsShape(SHAPE_POLYGON);
	m_pTarget->SetPhysicsBody(BODY_DYNAMIC);
	m_pTarget->SetEntityType(ENTITY_TARGET);
	m_pTarget->Init(_rWorld);

	m_pPulleyJointDef = new b2PulleyJointDef();
	m_pPulleyJointDef->bodyA = m_pTarget->GetBody();
	m_pPulleyJointDef->bodyB = m_pWeight->GetBody();
	m_pPulleyJointDef->groundAnchorA = m_pGear1->GetBody()->GetPosition();
	m_pPulleyJointDef->groundAnchorB = m_pGear2->GetBody()->GetPosition();
	m_pPulleyJointDef->localAnchorA = m_pTarget->GetBody()->GetPosition();
	m_pPulleyJointDef->localAnchorB = m_pWeight->GetBody()->GetPosition();
	m_pPulleyJointDef->lengthA = 0.5f;
	m_pPulleyJointDef->lengthB = 0.75f;
	m_pPulleyJointDef->ratio = 0.5f;
	m_pPulleyJoint = (b2PulleyJoint*)_rWorld.CreateJoint(m_pPulleyJointDef);
}

void CPulleySystem::Render(bool _bDebugMode)
{
	m_pGear1->Render(_bDebugMode);
	m_pGear2->Render(_bDebugMode);
	m_pWeight->Render(_bDebugMode);

	// If the target exists
	if (m_pTarget != nullptr)
	{
		// Render the target
		m_pTarget->Render(_bDebugMode);
	}
}

void CPulleySystem::Update(GLfloat _fDelta, b2World& _rWorld)
{
	m_pGear1->Update(_fDelta);
	m_pGear2->Update(_fDelta);
	m_pWeight->Update(_fDelta);

	CUserData* pTargetData = nullptr;

	// If the target exists
	if (m_pTarget != nullptr)
	{
		// Update the target
		pTargetData = (CUserData*)m_pTarget->GetBody()->GetUserData();
		m_pTarget->Update(_fDelta);
	}

	// If the target has no health left
	if (pTargetData != nullptr && pTargetData->m_fHealth <= 0.0f)
	{
		// Destroy the joint and the target, which will set the weight to fall on to the seesaw
		_rWorld.DestroyJoint(m_pPulleyJoint);
		_rWorld.DestroyBody(m_pTarget->GetBody());

		delete m_pTarget;
		m_pTarget = nullptr;

		m_pWeight->GetBody()->SetLinearVelocity(5.0f * m_pWeight->GetBody()->GetLinearVelocity());
	}
}