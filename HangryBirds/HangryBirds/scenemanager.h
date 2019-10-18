//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: scenemanager.h
// Description	: CScenemanager header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <vector>

// Local Includes
#include "sprite.h"
#include "menu.h"
#include "game.h"

// Types
enum ECurrentScene
{
	SCENE_MAINMENU = 0,
	SCENE_GAME = 1,
	SCENE_GAMEOVER = 2
};

enum EGameState
{
	STATE_LOSE = 0,
	STATE_WIN_GOOD = 1,
	STATE_WIN_GREAT = 2,
	STATE_WIN_OUTSTANDING = 3
};

// Constants

// Prototypes

class CSceneManager
{
	// Member functions
public:
	~CSceneManager();

	static CSceneManager& GetInstance();
	static void DestroyInstance();

	void SetCurrentScene(ECurrentScene _eCurrentScene);
	void SetGameLevel(GLuint _uiGameLevel);

	virtual void Init();
	virtual void Render();
	virtual void Update(GLfloat _fDelta);

private:
	CSceneManager();

	// Member variables
protected:
	static CSceneManager* s_pSceneManager;

private:
	CMenu* m_pMenu;
	CGame* m_pGame;
	CMenu* m_pGameOver;
	ECurrentScene m_eCurrentScene;
	EGameState m_eGameState;
	bool m_bIsFirstLevel{ false };
	GLuint m_uiGameLevel;
};