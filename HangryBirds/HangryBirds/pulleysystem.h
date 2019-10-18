//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: pulleysystem.h
// Description	: CPulleySystem header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes
#include "entity.h"
#include "plank.h"

// Types

// Constants

// Prototypes

class CPulleySystem
{
public:
	CPulleySystem(glm::vec2 _v2Gear1Pos, glm::vec2 _v2Gear1Size, glm::vec2 _v2Gear2Pos, glm::vec2 _v2Gear2Size);
	~CPulleySystem();

	virtual void Init(b2World& _rWorld);
	virtual void Render(bool _bDebugMode);
	virtual void Update(GLfloat _fDelta, b2World& _rWorld);

private:
	CEntity* m_pGear1;
	CEntity* m_pGear2;

	CEntity* m_pTarget;
	CEntity* m_pWeight;

	b2PulleyJointDef* m_pPulleyJointDef;
	b2PulleyJoint* m_pPulleyJoint;

	b2Vec2 m_v2Anchor1;
	b2Vec2 m_v2Anchor2;
	b2Vec2 m_v2GroundAnchor1;
	b2Vec2 m_v2GroundAnchor2;

	glm::vec2 m_v2Gear1Pos;
	glm::vec2 m_v2Gear1Size;
	glm::vec2 m_v2Gear2Pos;
	glm::vec2 m_v2Gear2Size;

	b2World* m_pWorld;
};
