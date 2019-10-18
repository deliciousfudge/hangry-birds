//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: userdata.cpp
// Description	: Controls userdata implementation logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "userdata.h"

// Static Variables

// Static Function Prototypes

// Implementation

CUserData::CUserData(EEntityType _eEntityType, float _fHealth)
	: m_eEntityType(_eEntityType)
	, m_fHealth(_fHealth)
{
}

CUserData::~CUserData()
{
}