//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: menu.h
// Description	: CMenu header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <vector>

// Local Includes
#include "TextLabel.h"

// Types
enum EMenuType
{
	MENU_MAIN = 0,
	MENU_GAMEOVER_LOSE = 1,
	MENU_GAMEOVER_WIN_GOOD = 2,
	MENU_GAMEOVER_WIN_GREAT = 3,
	MENU_GAMEOVER_WIN_OUTSTANDING = 4,
};

// Constants

// Prototypes

class CMenu
{
	// Member functions
public:
	CMenu(EMenuType _eMenuType, bool _bCanRestart = true, bool _bCanProgress = false);
	~CMenu();

	virtual void Init();
	virtual void Render();
	virtual void Update(GLfloat _fDelta);

	// Member variables
private:
	TextLabel* m_pTitle;
	TextLabel* m_pTagline;
	TextLabel* m_pProceed;
	TextLabel* m_pRestart;

	CSprite* m_pBackground1;
	CSprite* m_pBackground2;
	EMenuType m_eMenuType;
	float m_fBackgroundZoomScale;
	bool m_bIsZoomingIn;
	float m_fParallaxScrollSpeed;
	bool m_bCanProgress;
	bool m_bCanRestart;

	std::string m_sTitleText;
	std::string m_sTaglineText;
	std::string m_sProceedText;
	std::string m_sRestartText;

	glm::vec2 m_v2TitlePos;
	glm::vec2 m_v2TaglinePos;
	glm::vec2 m_v2ProceedPos;
	glm::vec2 m_v2RestartPos;
};