//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: menu.cpp
// Description	: Controls menu implementation logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes
#include "scenemanager.h"

// This include
#include "menu.h"

// Static Variables

// Static Function Prototypes

// Implementation

CMenu::CMenu(EMenuType _eMenuType, bool _bCanRestart, bool _bCanProgress)
	: m_eMenuType(_eMenuType)
	, m_fBackgroundZoomScale(2.5f)
	, m_bIsZoomingIn(true)
	, m_fParallaxScrollSpeed(0.2f)
	, m_bCanRestart(_bCanRestart)
	, m_bCanProgress(_bCanProgress)
{

}

CMenu::~CMenu()
{
	delete m_pBackground1;
	m_pBackground1 = 0;

	delete m_pBackground2;
	m_pBackground2 = 0;

	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pTagline;
	m_pTagline = nullptr;

	delete m_pProceed;
	m_pProceed = nullptr;

	delete m_pRestart;
	m_pRestart = nullptr;
}

void CMenu::Init()
{
	m_sProceedText = "Press P to Proceed";
	m_sRestartText = "Press R to Restart";

	m_v2ProceedPos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.5f);
	m_v2RestartPos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.4f);

	switch (m_eMenuType)
	{
	case MENU_MAIN:
	{
		m_sTitleText = "Hangry Birds";
		m_v2TitlePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.8f);
	}
	break;

	case MENU_GAMEOVER_LOSE:
	{
		m_sTitleText = "You Lose";
		m_v2TitlePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.35f, CUtility::GetInstance().fScrHeight * 0.8f);

		m_sTaglineText = "There's still food left! You'll get it next time";
		m_v2TaglinePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.2f, CUtility::GetInstance().fScrHeight * 0.6f);
	}
	break;

	case MENU_GAMEOVER_WIN_GOOD:
	{
		m_sTitleText = "Good!";
		m_v2TitlePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.39f, CUtility::GetInstance().fScrHeight * 0.8f);

		m_sTaglineText = "You've scraped a win, but you can do better";
		m_v2TaglinePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.15f, CUtility::GetInstance().fScrHeight * 0.6f);
	}
	break;

	case MENU_GAMEOVER_WIN_GREAT:
	{
		m_sTitleText = "Great!";
		m_v2TitlePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.39f, CUtility::GetInstance().fScrHeight * 0.8f);

		m_sTaglineText = "Almost there, just shy of a complete performance";
		m_v2TaglinePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.1f, CUtility::GetInstance().fScrHeight * 0.6f);
	}
	break;

	case MENU_GAMEOVER_WIN_OUTSTANDING:
	{
		m_sTitleText = "Outstanding!";
		m_v2TitlePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.8f);

		m_sTaglineText = "In the words of Michael Fassbender: Perfection";
		m_v2TaglinePos = glm::vec2(CUtility::GetInstance().fScrWidth * 0.1f, CUtility::GetInstance().fScrHeight * 0.6f);
	}
	break;
	default:break;
	}

	m_pTitle = new TextLabel(m_sTitleText.c_str(), "Resources/Fonts/Orbitron-Bold.ttf", m_v2TitlePos);
	m_pTitle->SetScale(1.2f);
	m_pTitle->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));

	m_pTagline = new TextLabel(m_sTaglineText.c_str(), "Resources/Fonts/Orbitron-Medium.ttf", m_v2TaglinePos);
	m_pTagline->SetScale(0.8f);

	if (m_bCanProgress)
	{
		m_pProceed = new TextLabel(m_sProceedText.c_str(), "Resources/Fonts/Orbitron-Medium.ttf", m_v2ProceedPos);
		m_pProceed->SetScale(0.8f);
	}

	if (m_bCanRestart)
	{
		m_pRestart = new TextLabel(m_sRestartText.c_str(), "Resources/Fonts/Orbitron-Medium.ttf", m_v2RestartPos);
		m_pRestart->SetScale(0.8f);
	}

	m_pBackground1 = new CSprite(glm::vec2(0.0f), glm::vec2(1.0f));
	m_pBackground1->SetSprite(CUtility::GetInstance().ksSpriteMenuBackground.c_str());
	m_pBackground1->SetScale(glm::vec2(m_fBackgroundZoomScale));

	m_pBackground2 = new CSprite(glm::vec2(0.0f), glm::vec2(1.0f));
	m_pBackground2->SetSprite(CUtility::GetInstance().ksSpriteMenuBackground.c_str());
	m_pBackground2->SetScale(glm::vec2(m_fBackgroundZoomScale));

	m_pBackground1->Init();
	m_pBackground2->Init();
}

void CMenu::Render()
{
	m_pBackground1->Render();
	m_pBackground2->Render();
	
	m_pTitle->Render();
	m_pTagline->Render();

	if (m_pProceed != nullptr)
	{
		m_pProceed->Render();
	}
	
	if (m_pRestart != nullptr)
	{
		m_pRestart->Render();
	}
}

void CMenu::Update(GLfloat _fDelta)
{
	if (m_pBackground1->GetLeft() >= CUtility::GetInstance().fScrWidth)
	{
		m_pBackground1->SetPos(glm::vec2(0.0f - (CUtility::GetInstance().fScrWidth / 2.0f), CUtility::GetInstance().fScrHeight / 2.0f));
	}
	else
	{
		m_pBackground1->SetPos(glm::vec2(m_pBackground1->GetPos().x + m_fParallaxScrollSpeed, m_pBackground1->GetPos().y));
	}
	
	if (m_pBackground2->GetLeft() >= CUtility::GetInstance().fScrWidth)
	{
		m_pBackground2->SetPos(glm::vec2(0.0f - (CUtility::GetInstance().fScrWidth / 2.0f), CUtility::GetInstance().fScrHeight / 2.0f));
	}
	else
	{
		m_pBackground2->SetPos(glm::vec2(m_pBackground2->GetPos().x + m_fParallaxScrollSpeed, m_pBackground2->GetPos().y));
	}

	m_pBackground1->Update(_fDelta);
	m_pBackground2->Update(_fDelta);

	unsigned char ucPKeyState = CInput::GetInstance().GetKeyState('p');
	unsigned char ucRKeyState = CInput::GetInstance().GetKeyState('r');

	if (m_eMenuType == MENU_MAIN)
	{
		if (ucPKeyState == INPUT_FIRST_PRESS)
		{
			CSceneManager::GetInstance().SetCurrentScene(SCENE_GAME);
		}
	}
	else if (m_eMenuType == MENU_GAMEOVER_LOSE || m_eMenuType == MENU_GAMEOVER_WIN_GOOD || m_eMenuType == MENU_GAMEOVER_WIN_GREAT || MENU_GAMEOVER_WIN_OUTSTANDING)
	{
		if (m_bCanProgress && CInput::GetInstance().GetKeyState('p') == INPUT_FIRST_PRESS)
		{
			CSceneManager::GetInstance().SetGameLevel(2);
			CSceneManager::GetInstance().SetCurrentScene(SCENE_GAME);
		}

		if (ucRKeyState == INPUT_FIRST_PRESS)
		{
			CSceneManager::GetInstance().SetCurrentScene(SCENE_GAME);
		}
	}

	switch (m_eMenuType)
	{
	case MENU_MAIN:
	{
		m_pTitle->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.8f));
		m_pProceed->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.5f));
	}
	break;

	case MENU_GAMEOVER_LOSE:
	{
		m_pTitle->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.35f, CUtility::GetInstance().fScrHeight * 0.8f));
		m_pTagline->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.2f, CUtility::GetInstance().fScrHeight * 0.6f));
		m_pRestart->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.4f));
	}
	break;

	case MENU_GAMEOVER_WIN_GOOD:
	{
		m_pTitle->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.39f, CUtility::GetInstance().fScrHeight * 0.8f));
		m_pTagline->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.15f, CUtility::GetInstance().fScrHeight * 0.6f));
		m_pRestart->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.4f));
	}
	break;

	case MENU_GAMEOVER_WIN_GREAT:
	{
		m_pTitle->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.39f, CUtility::GetInstance().fScrHeight * 0.8f));
		m_pTagline->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.1f, CUtility::GetInstance().fScrHeight * 0.6f));
		m_pRestart->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.4f));
	}
	break;

	case MENU_GAMEOVER_WIN_OUTSTANDING:
	{
		m_pTitle->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.8f));
		m_pTagline->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.1f, CUtility::GetInstance().fScrHeight * 0.6f));
		m_pRestart->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.33f, CUtility::GetInstance().fScrHeight * 0.4f));
	}
	break;
	default:break;
	}
}