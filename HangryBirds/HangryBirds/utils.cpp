//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: utils.cpp
// Description	: Stores settings and assorted logic for managing instances within the program
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "utils.h"

// Static Variables
CUtility* CUtility::s_pUtility = nullptr;

// Static Function Prototypes

// Implementation

CUtility::CUtility()
{

}

CUtility::~CUtility()
{
}

CUtility& CUtility::GetInstance()
{
	if (s_pUtility == nullptr)
	{
		s_pUtility = new CUtility();
	}

	return (*s_pUtility);
}

void CUtility::DestroyInstance()
{
	delete s_pUtility;
	s_pUtility = nullptr;
}
