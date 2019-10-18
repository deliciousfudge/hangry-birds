//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: scenemanager.cpp
// Description	: Initialises and controls scenes within the game
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "scenemanager.h"

// Static Variables
CSceneManager* CSceneManager::s_pSceneManager = nullptr;

// Static Function Prototypes

// Implementation

CSceneManager::CSceneManager()
	: m_eCurrentScene(SCENE_MAINMENU)
	, m_pMenu(new CMenu(MENU_MAIN, false, true))
	, m_pGame(nullptr)
	, m_pGameOver(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	delete m_pMenu;
	m_pMenu = nullptr;

	if (m_pGame != nullptr)
	{
		m_pGame->ClearGameEntities();
	}

	delete m_pGame;
	m_pGame = nullptr;

	delete m_pGameOver;
	m_pGameOver = nullptr;
}

CSceneManager& CSceneManager::GetInstance()
{
	if (s_pSceneManager == nullptr)
	{
		s_pSceneManager = new CSceneManager();
	}
	
	return (*s_pSceneManager);
}

void CSceneManager::DestroyInstance()
{
	if (s_pSceneManager != nullptr)
	{
		delete s_pSceneManager;
		s_pSceneManager = 0;
	}
}

void CSceneManager::SetCurrentScene(ECurrentScene _eCurrentScene)
{
	// Change to the new scene
	m_eCurrentScene = _eCurrentScene;

	switch (m_eCurrentScene)
	{
	case SCENE_MAINMENU:
	{
		if (m_pMenu != nullptr)
		{
			delete m_pMenu;
		}

		m_pMenu = new CMenu(MENU_MAIN, false, true);
		m_pMenu->Init();
	}
	break;

	case SCENE_GAME:
	{
		if (m_pGame != nullptr)
		{
			delete m_pGame;
		}
		
		m_pGame = new CGame(m_uiGameLevel);
		m_pGame->Init();
	}
	break;

	case SCENE_GAMEOVER:
	{
		if (m_pGameOver != nullptr)
		{
			delete m_pGameOver;
		}

		switch (m_eGameState)
		{
		case STATE_LOSE:
		{
			m_pGameOver = new CMenu(MENU_GAMEOVER_LOSE);
		}
		break;

		case STATE_WIN_GOOD:
		{
			m_pGameOver = new CMenu(MENU_GAMEOVER_WIN_GOOD, true, m_bIsFirstLevel);
		}
		break;

		case STATE_WIN_GREAT:
		{
			m_pGameOver = new CMenu(MENU_GAMEOVER_WIN_GREAT, true, m_bIsFirstLevel);
		}
		break;

		case STATE_WIN_OUTSTANDING:
		{
			m_pGameOver = new CMenu(MENU_GAMEOVER_WIN_OUTSTANDING, true, m_bIsFirstLevel);
		}
		break;
		default:break;
		}
		
		m_pGameOver->Init();
	}
	break;

	default:break;
	}
}

void CSceneManager::SetGameLevel(GLuint _uiGameLevel)
{
	m_uiGameLevel = _uiGameLevel;
}

void CSceneManager::Init()
{
	m_uiGameLevel = CUtility::GetInstance().kuiStartingLevel;
	m_pMenu->Init();
}

void CSceneManager::Render()
{
	switch (m_eCurrentScene)
	{
	case SCENE_MAINMENU:
	{
		m_pMenu->Render();
	}
	break;

	case SCENE_GAME:
	{
		m_pGame->Render();
	}
	break;

	case SCENE_GAMEOVER:
	{
		m_pGameOver->Render();
	}
	break;

	default:break;
	}
}

void CSceneManager::Update(GLfloat _fDelta)
{
	if (m_pGame != nullptr)
	{
		m_bIsFirstLevel = m_pGame->GetLevel() == 1;

		if (m_eCurrentScene == SCENE_GAME)
		{
			if (m_pGame->GetResult() != RESULT_NONE)
			{
				switch (m_pGame->GetResult())
				{
				case RESULT_LOSE:
				{
					m_eGameState = STATE_LOSE;
				}
				break;
				
				case RESULT_WIN_GOOD:
				{
					m_eGameState = STATE_WIN_GOOD;
				}
				break;

				case RESULT_WIN_GREAT:
				{
					m_eGameState = STATE_WIN_GREAT;
				}
				break;

				case RESULT_WIN_OUTSTANDING:
				{
					m_eGameState = STATE_WIN_OUTSTANDING;
				}
				break;
				
				default:break;
				}

				SetCurrentScene(SCENE_GAMEOVER);
			}
		}
	}

	switch (m_eCurrentScene)
	{
	case SCENE_MAINMENU:
	{
		m_pMenu->Update(_fDelta);
	}
	break;

	case SCENE_GAME:
	{
		m_pGame->Update(_fDelta);
	}
	break;

	case SCENE_GAMEOVER:
	{
		m_pGameOver->Update(_fDelta);
	}
	break;

	default:break;
	}
}