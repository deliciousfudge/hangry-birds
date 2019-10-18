//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: userdata.h
// Description	: CUserData header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <string>

// Local Includes

// Types
enum EEntityType
{
	ENTITY_UNASSIGNED = 0,
	ENTITY_BIRD = 1,
	ENTITY_ENEMY = 2,
	ENTITY_BPLANK = 3, // Breakable plank
	ENTITY_PLANK = 4, // Unbreakable plank
	ENTITY_GROUND = 5,
	ENTITY_WRECKINGBALL = 6,
	ENTITY_TARGET = 7,
	ENTITY_WEIGHT = 8,
};

enum EBirdType
{
	BIRD_UNASSIGN = 0,
	BIRD_HEAVY = 1,
	BIRD_BOOST = 2,
	BIRD_DIVEBOMB = 3,
};

// Constants

// Prototypes

class CUserData
{
	// Member methods
public:
	CUserData(EEntityType _eEntityType, float _fHealth);
	~CUserData();

	// Member variables
public:
	EEntityType m_eEntityType;
	float m_fHealth;
	EBirdType m_eBirdType{ BIRD_UNASSIGN };
};
