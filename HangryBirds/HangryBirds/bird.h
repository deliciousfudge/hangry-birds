//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: bird.h
// Description	: CBird header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <algorithm>

// Local Includes
#include "entity.h"
#include "input.h"

// Types

// Constants

// Prototypes

class CBird : public CEntity
{
	// Member functions
public:
	CBird(glm::vec2 _v2Pos, glm::vec2 _v2Size, EBirdType _eBirdType, int _iSpanX = 1, int _iSpanY = 1, int _iNumSpr = 1);
    virtual	~CBird();

	virtual void Init(b2World& _krWorld);
	virtual void Render(bool _bDebugMode);
	virtual void Update(GLfloat _fDelta);

	bool GetIsActive() const;
	void SetIsActive(bool _bIsActive);

	EBirdType& GetType() const;
	void SetType(EBirdType _eType);

	// Member variables
private:
	bool m_bIsActive{ false }; // Used to record whether or not the player has been flung from the slingshot
	EBirdType m_eBirdType{ BIRD_UNASSIGN };
};