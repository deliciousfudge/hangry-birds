//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: contactlistener.h
// Description	: CContactListener header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes
#include "entity.h"
#include "userdata.h"

// Types

// Constants

// Prototypes

class CContactListener : public b2ContactListener
{
	// Member functions
public:
	CContactListener();
	~CContactListener();

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	void CheckPlayer(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse);
	void CheckEnemy(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse);
	void CheckBreakablePlank(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse);
	void CheckTarget(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse);
	void CheckWeight(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse);
};

