//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: level.h
// Description	: Level header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <vector>

// Local Includes
#include "bird.h"
#include "enemy.h"
#include "entity.h"
#include "TextLabel.h"
#include "ground.h"
#include "plank.h"
#include "seesaw.h"
#include "wreckingball.h"
#include "pulleysystem.h"
#include "contactlistener.h"

// Types
enum EGameResult
{
	RESULT_NONE = 0,
	RESULT_LOSE = 1,
	RESULT_WIN_GOOD = 2,
	RESULT_WIN_GREAT = 3,
	RESULT_WIN_OUTSTANDING = 4
};

// Constants

// Prototypes

class CGame
{
	// Member functions
public:
	CGame(unsigned int _uiLevel);
	virtual ~CGame();

	virtual void Init();
	virtual void Render();
	virtual void Update(GLfloat _fDelta);

	CBird* GetBird();
	CEnemy* GetEnemy(unsigned int _uiID);

	void ResetLevel();

	void SetScore(GLuint _uiScore);
	GLuint GetScore() const;

	GLuint GetLevel() const;
	void SetLevel(GLuint _uiLevel);

	EGameResult GetResult() const;

	void LevelSetup();
	void ClearGameEntities();

	void CheckForBirdDeath();
	void CheckForBirdEffects();
	void CheckForSlingshotFiring(float _fDelta);
	void CheckForBirdSlowdown();

protected:
	void ProcessCheckForLoss();
	void ProcessCheckForWin();

	// Member variables
private:
	CSprite* m_pBackground;
	std::vector<CBird*> m_vecBirds;
	std::vector<CEnemy*> m_vecEnemies;
	CGround* m_pGround;
	std::vector<CPlank*> m_vecPlanks;
	CSprite* m_pSlingshotBase;
	CSprite* m_pSlingshotArm;
	CSeesaw* m_pSeesaw;
	CSprite* m_pWreckingBallPole;
	CWreckingBall* m_pWreckingBall;
	CPulleySystem* m_pPulleySystem;
	TextLabel* m_tScoreLabel;

	GLuint m_uiCurrentPlayer;

	GLuint m_uiLevel;
	GLuint m_uiScore;

	EGameResult m_eGameResult{ RESULT_NONE };
	bool m_bGameActive{ false };

	b2Vec2 m_v2SlingshotCenter;
	bool m_bBoostUsed;
	
	std::vector<glm::vec2> m_vecBirdStartPos;
	std::vector<glm::vec2> m_vecEnemyStartPos;
	std::vector<PlankAttrib> m_vecPlankAttribs;

	const char* m_kcpBackgroundPath;
	const char* m_kcpPlatSpritePath;

	b2World* m_pWorld;
	bool m_bDebugMode{ false };

	CContactListener* m_pContactListener; // Used to assign damage to entities when appropriate

	bool m_bIsBirdShootable{ false };
	bool m_bIsBirdSelectable{ false };

	GLuint m_uiFPS{ 0 };

	float m_fPixelToMetre{ 0.0f };
	float m_fScreenBorder{ 0.0f };
	float m_fImpulseScalar{ 2.0f };
};

