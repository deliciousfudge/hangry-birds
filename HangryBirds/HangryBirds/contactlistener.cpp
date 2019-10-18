//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: contactlistener.cpp
// Description	: Provides custom collision logic for Box2D collisions
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes

// Local Includes

// This include
#include "contactlistener.h"

// Static Variables

// Static Function Prototypes

// Implementation

CContactListener::CContactListener()
{
}

CContactListener::~CContactListener()
{
}

void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	b2Body* pBodyA = contact->GetFixtureA()->GetBody();
	b2Body* pBodyB = contact->GetFixtureB()->GetBody();

	CUserData* pDataA = (CUserData*)contact->GetFixtureA()->GetBody()->GetUserData();
	CUserData* pDataB = (CUserData*)(contact->GetFixtureB()->GetBody()->GetUserData());
	
	CheckPlayer(*pDataA, *pDataB, *pBodyA, *pBodyB, impulse);
	CheckEnemy(*pDataA, *pDataB, *pBodyA, *pBodyB, impulse);
	CheckBreakablePlank(*pDataA, *pDataB, *pBodyA, *pBodyB, impulse);
	CheckTarget(*pDataA, *pDataB, *pBodyA, *pBodyB, impulse);
	CheckWeight(*pDataA, *pDataB, *pBodyA, *pBodyB, impulse);
}

void CContactListener::CheckPlayer(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse)
{
	// If the first entity is a bird
	if (_rDataA.m_eEntityType == ENTITY_BIRD)
	{
		// If the second entity is an enemy, plank, or ground
		if ((_rDataB.m_eEntityType == ENTITY_ENEMY) ||
			(_rDataB.m_eEntityType == ENTITY_PLANK) ||
			(_rDataB.m_eEntityType == ENTITY_BPLANK) ||
			(_rDataB.m_eEntityType == ENTITY_GROUND))
		{
			// Reduce the bird's health by the collision impulse
			_rDataA.m_fHealth -= impulse->normalImpulses[0];
		}

		if (_rDataB.m_eEntityType == ENTITY_WRECKINGBALL)
		{
			_rDataA.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageWreckingBall;
		}
	}

	// If the second entity is a bird
	if (_rDataB.m_eEntityType == ENTITY_BIRD)
	{
		// If the first entity is an enemy, plank, or ground
		if ((_rDataA.m_eEntityType == ENTITY_ENEMY) ||
			(_rDataA.m_eEntityType == ENTITY_PLANK) ||
			(_rDataA.m_eEntityType == ENTITY_BPLANK) ||
			(_rDataA.m_eEntityType == ENTITY_GROUND))
		{
			// Reduce the bird's health by the collision impulse
			_rDataB.m_fHealth -= impulse->normalImpulses[0];
		}

		if (_rDataA.m_eEntityType == ENTITY_WRECKINGBALL)
		{
			_rDataB.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageWreckingBall;
		}
	}
}

void CContactListener::CheckEnemy(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse)
{
	// If the first entity is an enemy
	if (_rDataA.m_eEntityType == ENTITY_ENEMY)
	{
		// If the second entity is ground, an enemy, or a plank
		if ((_rDataB.m_eEntityType == ENTITY_GROUND) ||
			(_rDataB.m_eEntityType == ENTITY_ENEMY) ||
			(_rDataB.m_eEntityType == ENTITY_PLANK) ||
			(_rDataB.m_eEntityType == ENTITY_BPLANK))
		{
			// Reduce the enemy's health by the collision impulse
			_rDataA.m_fHealth -= impulse->normalImpulses[0];
		}

		// If the second entity is a bird
		if (_rDataB.m_eEntityType == ENTITY_BIRD)
		{
			// If the bird type is a heavy, do more damage
			if (_rDataB.m_eBirdType == BIRD_HEAVY)
			{
				// Do an increased level of damage
				_rDataA.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdHeavy;
			}
			else
			{
				// Otherwise do the regular amount of bird damage
				_rDataA.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdOther;
			}
		}

		// If the second entity is a wrecking ball
		if (_rDataB.m_eEntityType == ENTITY_WRECKINGBALL)
		{
			// Reduce the enemy's health by the wrecking ball rate
			_rDataA.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageWreckingBall;
		}
	}

	// If the second entity is an enemy
	if (_rDataB.m_eEntityType == ENTITY_ENEMY)
	{
		// If the first entity is ground, an enemy, or a plank
		if ((_rDataA.m_eEntityType == ENTITY_GROUND) ||
			(_rDataA.m_eEntityType == ENTITY_ENEMY) ||
			(_rDataA.m_eEntityType == ENTITY_PLANK) ||
			(_rDataA.m_eEntityType == ENTITY_BPLANK))
		{
			// Reduce the enemy's health by the collision impulse
			_rDataB.m_fHealth -= impulse->normalImpulses[0];
		}
		// If the first entity is a bird
		if (_rDataA.m_eEntityType == ENTITY_BIRD)
		{
			// If the bird type is a heavy
			if (_rDataA.m_eBirdType == BIRD_HEAVY)
			{
				// Do an increased level of damage
				_rDataB.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdHeavy;
			}
			else
			{
				// Otherwise do the regular amount of bird damage
				_rDataB.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdOther;
			}
		}

		// If the first entity is a wrecking ball
		if (_rDataA.m_eEntityType == ENTITY_WRECKINGBALL)
		{
			// Reduce the enemy's health by the wrecking ball rate
			_rDataB.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageWreckingBall;
		}
	}
}

void CContactListener::CheckBreakablePlank(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse)
{
	// If the first entity is a breakable plank
	if (_rDataA.m_eEntityType == ENTITY_BPLANK)
	{
		// If the second entity is ground, an enemy or a non-breakable plank
		if ((_rDataB.m_eEntityType == ENTITY_GROUND) ||
			(_rDataB.m_eEntityType == ENTITY_ENEMY) ||
			(_rDataB.m_eEntityType == ENTITY_PLANK))
		{
			// Reduce the plank's health by the collision impulse
			_rDataA.m_fHealth -= impulse->normalImpulses[0];
		}

		// If the second entity is a bird
		if (_rDataB.m_eEntityType == ENTITY_BIRD)
		{
			// If the bird type is a heavy
			if (_rDataB.m_eBirdType == BIRD_HEAVY)
			{
				// Do an increased level of damage
				_rDataA.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdHeavy;
			}
			else
			{
				// Otherwise do the regular amount of bird damage
				_rDataA.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdOther;
			}
		}

		if (_rDataB.m_eEntityType == ENTITY_WRECKINGBALL)
		{
			// Reduce the plank's health by the wrecking ball damage factor
			_rDataA.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageWreckingBall;
		}
	}

	// If the second entity is a breakable plank
	if (_rDataB.m_eEntityType == ENTITY_BPLANK)
	{
		// If the first entity is ground, an enemy or a non-breakable plank
		if ((_rDataA.m_eEntityType == ENTITY_GROUND) ||
			(_rDataA.m_eEntityType == ENTITY_ENEMY) ||
			(_rDataA.m_eEntityType == ENTITY_PLANK))
		{
			// Reduce the plank's health by the collision impulse
			_rDataB.m_fHealth -= impulse->normalImpulses[0];
		}

		// If the first entity is a bird
		if (_rDataA.m_eEntityType == ENTITY_BIRD)
		{
			// If the bird type is a heavy, do more damage
			if (_rDataA.m_eBirdType == BIRD_HEAVY)
			{
				_rDataB.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdHeavy;
			}
			else
			{
				_rDataB.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageBirdOther;
			}
		}

		// If the first entity is a wrecking ball
		if (_rDataA.m_eEntityType == ENTITY_WRECKINGBALL)
		{
			// Reduce the plank's health by the wrecking ball damage factor
			_rDataB.m_fHealth -= impulse->normalImpulses[0] * CUtility::GetInstance().kfDamageWreckingBall;
		}
	}
}

void CContactListener::CheckTarget(CUserData& _rDataA, CUserData& _rDataB, b2Body& _rBodyA, b2Body& _rBodyB, const b2ContactImpulse* impulse)
{
	// If the first entity is a target
	if (_rDataA.m_eEntityType == ENTITY_TARGET)
	{
		// If the second entity is a bird or enemy
		if ((_rDataB.m_eEntityType == ENTITY_BIRD) ||
			(_rDataB.m_eEntityType == ENTITY_ENEMY))
		{
			// Set the target's health to 0
			_rDataA.m_fHealth = 0.0f;
		}
	}

	// If the second entity is a target
	if (_rDataB.m_eEntityType == ENTITY_TARGET)
	{
		// If the first entity is a bird or enemy
		if ((_rDataA.m_eEntityType == ENTITY_BIRD) ||
			(_rDataA.m_eEntityType == ENTITY_ENEMY))
		{
			// Set the target's health to 0
			_rDataB.m_fHealth = 0.0f;
		}
	}
}

void CContactListener::CheckWeight(CUserData & _rDataA, CUserData & _rDataB, b2Body & _rBodyA, b2Body & _rBodyB, const b2ContactImpulse * impulse)
{
	// If the first entity is a weight
	if (_rDataA.m_eEntityType == ENTITY_WEIGHT)
	{
		// If the second entity is an enemy
		if (_rDataB.m_eEntityType == ENTITY_ENEMY)
		{
			// Set the enemy's health to 0
			_rDataB.m_fHealth = 0.0f;
		}
	}

	// If the second entity is a weight
	if (_rDataB.m_eEntityType == ENTITY_WEIGHT)
	{
		// If the first entity is an enemy
		if (_rDataA.m_eEntityType == ENTITY_ENEMY)
		{
			// Set the enemy's health to 0
			_rDataA.m_fHealth = 0.0f;
		}
	}
}
