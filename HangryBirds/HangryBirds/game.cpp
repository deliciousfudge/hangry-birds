//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: game.cpp
// Description	: Controls game implementation logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "game.h"

// Static Variables

// Static Function Prototypes

// Implementation

CGame::CGame(unsigned int _uiLevel)
	: m_uiLevel(_uiLevel)
	, m_uiScore(0)
{

}

CGame::~CGame()
{
	ClearGameEntities();
}

void CGame::Init()
{
	LevelSetup();
	m_bGameActive = true;
	m_fPixelToMetre = CCamera::GetInstance().GetPixelToMetre();
	m_fScreenBorder = CUtility::GetInstance().fScrWidth / m_fPixelToMetre;
}

void CGame::Render()
{
	// If a game is in progress
	if (m_bGameActive)
	{
		// Make the appropriate render calls, assuming the given entity exists (is not null)
	
		m_pBackground->Render();

		m_pGround->Render(m_bDebugMode);

		for (unsigned int i = 0; i < m_vecPlanks.size(); i++)
		{
			m_vecPlanks[i]->Render(m_bDebugMode);
		}

		if (m_pSlingshotBase != nullptr)
		{
			m_pSlingshotBase->Render();
		}

		if (m_pSeesaw != nullptr)
		{
			m_pSeesaw->Render(m_bDebugMode);
		}

		if (m_pWreckingBallPole != nullptr)
		{
			m_pWreckingBallPole->Render();
		}

		if (m_pPulleySystem != nullptr)
		{
			m_pPulleySystem->Render(m_bDebugMode);
		}
		
		for (GLuint i = 0; i < m_vecBirds.size(); ++i)
		{
			m_vecBirds[i]->Render(m_bDebugMode);
		}

		for (unsigned int i = 0; i < m_vecEnemies.size(); i++)
		{
			m_vecEnemies[i]->Render(m_bDebugMode);
		}

		if (m_pWreckingBall != nullptr)
		{
			m_pWreckingBall->Render(m_bDebugMode);
		}

		if (m_pSlingshotArm != nullptr)
		{
			m_pSlingshotArm->Render();
		}

		m_tScoreLabel->Render();
	}
}

void CGame::Update(GLfloat _fDelta)
{
	// If a game is in progress
	if (m_bGameActive)
	{
		// Update the physics info of all physics-based entities in the game world	
		m_pWorld->Step(CUtility::GetInstance().kfTimestep, CUtility::GetInstance().kuiVelocityIters, CUtility::GetInstance().kuiPositionIters);

		// Make the appropriate update calls, assuming the given entity exists (is not null)
		m_pBackground->Update(_fDelta);
		m_pGround->Update(_fDelta);

		for (GLuint i = 0; i < m_vecBirds.size(); ++i)
		{
			m_vecBirds[i]->Update(_fDelta);
		}

		for (unsigned int i = 0; i < m_vecEnemies.size(); i++)
		{
			m_vecEnemies[i]->Update(_fDelta);
		}

		for (unsigned int i = 0; i < m_vecPlanks.size(); i++)
		{
			m_vecPlanks[i]->Update(_fDelta);
		}

		if (m_pSeesaw != nullptr)
		{
			m_pSeesaw->Update(_fDelta);
		}

		if (m_pWreckingBallPole != nullptr)
		{
			m_pWreckingBallPole->Update(_fDelta);
		}
	
		if (m_pWreckingBall != nullptr)
		{
			m_pWreckingBall->Update(_fDelta);
		}

		if (m_pPulleySystem != nullptr)
		{
			m_pPulleySystem->Update(_fDelta, *m_pWorld);
		}
		
		if (m_pSlingshotBase != nullptr)
		{
			m_pSlingshotBase->Update(_fDelta);
		}

		if (m_pSlingshotArm != nullptr)
		{
			m_pSlingshotArm->Update(_fDelta);
		}
		
		m_tScoreLabel->SetText("Score: " + std::to_string(m_uiScore));
		m_tScoreLabel->SetPosition(glm::vec2(CUtility::GetInstance().fScrWidth * 0.8f, CUtility::GetInstance().fScrHeight * 0.85f));

		// If the tilde key is pressed, switch between regular rendering and debug rendering
		if (CInput::GetInstance().GetKeyState('`') == INPUT_FIRST_PRESS)
		{
			m_bDebugMode ? m_bDebugMode = false : m_bDebugMode = true;
		}

		CheckForBirdDeath();

		// If there are still birds left
		if (m_vecBirds.size() > 0)
		{
			// Check to see if any of the bird effects (boost and divebomb) can be / are used
			CheckForBirdEffects();

			// Check for and take the appropriate slingshot-related action
			CheckForSlingshotFiring(_fDelta);

			// Check to see if the bird has slowed down to an idle, and if so take steps to eliminate the bid
			CheckForBirdSlowdown();
		}
	}

	// If there are enemies remaining
	if (m_vecEnemies.size() > 0)
	{
		// For each remaining enemy
		for (GLuint i = 0; i < m_vecEnemies.size(); ++i)
		{
			// Get the user data for that enemy
			CUserData* pEnemyData = (CUserData*)m_vecEnemies[i]->GetBody()->GetUserData();
			bool bOutsideBounds = (m_vecEnemies[i]->GetPos().x > m_fScreenBorder) || (m_vecEnemies[i]->GetPos().x < -(m_fScreenBorder));

			// If the enemy has no health left or leaves the play space
			if (pEnemyData->m_fHealth <= 0.0f || bOutsideBounds)
			{
				// Remove the enemy from any physics simulations
				m_pWorld->DestroyBody(m_vecEnemies[i]->GetBody());
				
				// Remove the enemy from memory and the enemy array
				delete m_vecEnemies[i];
				m_vecEnemies[i] = nullptr;
				m_vecEnemies.erase(m_vecEnemies.begin() + i);
				
				// Update the player's score by the appropriate number of points
				m_uiScore += CUtility::GetInstance().kuiEnemyPoints;
			}
		}
	}

	// If there are planks remaining
	if (m_vecPlanks.size() > 0)
	{
		// For each plank
		for (GLuint i = 0; i < m_vecPlanks.size(); ++i)
		{
			// Get the user data for the current plank
			CUserData* pPlankData = (CUserData*)m_vecPlanks[i]->GetBody()->GetUserData();
			
			// If the plank has no health left
			if (pPlankData->m_fHealth <= 0.0f)
			{
				// Remove the plank from physics simulations
				m_pWorld->DestroyBody(m_vecPlanks[i]->GetBody());
				
				// Remove the plank both from memory and the planks vector
				delete m_vecPlanks[i];
				m_vecPlanks[i] = nullptr;
				m_vecPlanks.erase(m_vecPlanks.begin() + i);
				
				// Update the player's score by the appropriate number of points
				m_uiScore += CUtility::GetInstance().kuiPlankPoints;
			}
		}
	}

	// If the player presses the restart button
	if (CInput::GetInstance().GetKeyState('r') == INPUT_FIRST_PRESS)
	{
		// Reset the current level
		ResetLevel();
	}

	// If the player presses the pass level button
	if (CInput::GetInstance().GetKeyState('p') == INPUT_FIRST_PRESS)
	{
		m_vecEnemies.clear();
		m_uiScore = 30000;
	}

	// Check to see if gameplay should be concluded
	ProcessCheckForLoss();
	ProcessCheckForWin();
}

CBird* CGame::GetBird()
{
	return m_vecBirds[0];
}

CEnemy* CGame::GetEnemy(unsigned int _uiID)
{
	return m_vecEnemies[_uiID];
}

void CGame::ResetLevel()
{
	// Set the game as inactive (stops rendering and updating)
	m_bGameActive = false;

	// Destroy any running game entities
	ClearGameEntities();
	
	// Recreate game entities
	LevelSetup();

	// Set the game as active
	m_bGameActive = true;
}

void CGame::SetScore(GLuint _uiScore)
{
	m_uiScore = _uiScore;
}

GLuint CGame::GetScore() const
{
	return m_uiScore;
}

GLuint CGame::GetLevel() const
{
	return m_uiLevel;
}

void CGame::SetLevel(GLuint _uiLevel)
{
	m_uiLevel = _uiLevel;
}

EGameResult CGame::GetResult() const
{
	return m_eGameResult;
}

void CGame::LevelSetup()
{
	// Create a b2World object for physics simulations and set the gravity
	m_pWorld = new b2World(CUtility::GetInstance().kv2Gravity);

	// Create a custom contact listener and set it as the default contact listener
	m_pContactListener = new CContactListener();
	m_pWorld->SetContactListener(m_pContactListener);

	m_bIsBirdShootable = false;
	m_bBoostUsed = false;

	m_kcpBackgroundPath = "Resources/Art/levelbg.png";
	m_pBackground = new CSprite(glm::vec2(0.0f), glm::vec2(100.0f));
	m_pBackground->SetSprite(m_kcpBackgroundPath);
	m_pBackground->Init();

	m_pGround = new CGround(glm::vec2(0.0f, -14.0f), glm::vec2(40.0f, 0.5f));
	m_pGround->SetSprite(CUtility::GetInstance().ksSpriteGround.c_str());
	m_pGround->SetScale(glm::vec2(2.0f));
	m_pGround->Init(*m_pWorld);

	// Set up entities specific to the current level
	switch (m_uiLevel)
	{
	// If the current level is 1
	case 1:
	{
		// Set up the wrecking ball object
		m_pWreckingBallPole = new CSprite(glm::vec2(7.5f, m_pGround->GetPos().y + 14.0f), glm::vec2(15.0f));
		m_pWreckingBallPole->SetScale(glm::vec2(2.0f));
		m_pWreckingBallPole->SetSprite(CUtility::GetInstance().ksSpriteWreckingPole.c_str());
		m_pWreckingBallPole->Init();

		m_pWreckingBall = new CWreckingBall(
			glm::vec2(m_pWreckingBallPole->GetPos().x, m_pWreckingBallPole->GetPos().y + m_pWreckingBallPole->GetSize().y),
			m_pWreckingBallPole->GetSize() * 0.1f,
			glm::vec2(m_pWreckingBallPole->GetPos().x, m_pGround->GetPos().y + 4.0f),
			glm::vec2(1.5f),
			m_pWreckingBallPole->GetSize().y * 1.55f
		);
		m_pWreckingBall->Init(*m_pWorld);

		// Define any enemy start positions
		m_vecEnemyStartPos.push_back(glm::vec2(18.0f, m_pGround->GetPos().y + 8.5f));

		// Set up any enemy objects
		for (GLuint i = 0; i < m_vecEnemyStartPos.size(); ++i)
		{
			CEnemy* pEnemy = new CEnemy(0, m_vecEnemyStartPos[i], glm::vec2(0.5f));
			pEnemy->SetDensity(0.01f);
			pEnemy->SetRestitution(1.0f);
			pEnemy->Init(*m_pWorld);
			m_vecEnemies.push_back(pEnemy);
		}

		// Define any plank start positions
		// Base of the tower
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(13.15f, m_pGround->GetPos().y + 1.5f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(15.0f, m_pGround->GetPos().y + 1.5f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(17.0f, m_pGround->GetPos().y + 1.5f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(19.0f, m_pGround->GetPos().y + 1.5f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(21.0f, m_pGround->GetPos().y + 1.5f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(22.85f, m_pGround->GetPos().y + 1.5f), 90.0f, glm::vec2(1.0f, 0.3f)));

		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(14.0f, m_pGround->GetPos().y + 2.75f), 0.0f, glm::vec2(1.0f, 0.2f), true));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(16.0f, m_pGround->GetPos().y + 2.75f), 0.0f, glm::vec2(1.0f, 0.2f), true));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(18.0f, m_pGround->GetPos().y + 2.75f), 0.0f, glm::vec2(1.0f, 0.2f), true));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(20.0f, m_pGround->GetPos().y + 2.75f), 0.0f, glm::vec2(1.0f, 0.2f), true));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(22.0f, m_pGround->GetPos().y + 2.75f), 0.0f, glm::vec2(1.0f, 0.2f), true));

		// Second level of the tower
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(15.15f, m_pGround->GetPos().y + 4.0f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(16.85f, m_pGround->GetPos().y + 4.0f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(19.0f, m_pGround->GetPos().y + 4.0f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(21.0f, m_pGround->GetPos().y + 4.0f), 90.0f, glm::vec2(1.0f, 0.3f)));

		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(16.0f, m_pGround->GetPos().y + 5.25f), 0.0f, glm::vec2(1.0f, 0.25f), true));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(18.0f, m_pGround->GetPos().y + 5.25f), 0.0f, glm::vec2(1.0f, 0.25f), true));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(20.0f, m_pGround->GetPos().y + 5.25f), 0.0f, glm::vec2(1.0f, 0.25f), true));

		// Top of the tower
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(17.0f, m_pGround->GetPos().y + 6.50f), 90.0f, glm::vec2(1.0f, 0.3f)));
		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(19.0f, m_pGround->GetPos().y + 6.50f), 90.0f, glm::vec2(1.0f, 0.3f)));

		m_vecPlankAttribs.push_back(PlankAttrib(glm::vec2(18.0f, m_pGround->GetPos().y + 7.75f), 0.0f, glm::vec2(1.0f, 0.25f)));

		// Set up any plank objects
		for (GLuint i = 0; i < m_vecPlankAttribs.size(); ++i)
		{
			CPlank* pPlank = new CPlank(m_vecPlankAttribs[i].v2Pos, m_vecPlankAttribs[i].v2Size, m_vecPlankAttribs[i].bBreakable);
			pPlank->SetRot(glm::vec3(0.0f, 0.0f, glm::radians(m_vecPlankAttribs[i].fRot)));
			pPlank->Init(*m_pWorld);
			m_vecPlanks.push_back(pPlank);
		}
	}
	break;

	// If the current level is 2
	case 2:
	{
		// Set up the pulley system
		m_pPulleySystem = new CPulleySystem(glm::vec2(-2.0f, m_pGround->GetPos().y + 20.0f), glm::vec2(1.0f), glm::vec2(5.0f, m_pGround->GetPos().y + 20.0f), glm::vec2(1.0f));
		m_pPulleySystem->Init(*m_pWorld);

		// Set up the seesaw
		m_pSeesaw = new CSeesaw(glm::vec2(3.0f, m_pGround->GetPos().y + 1.5f), glm::vec2(1.0f));
		m_pSeesaw->Init(*m_pWorld);

		// Define any enemy start positions
		m_vecEnemyStartPos.push_back(glm::vec2(15.0f, m_pGround->GetPos().y + 1.0f));
		m_vecEnemyStartPos.push_back(glm::vec2(16.0f, m_pGround->GetPos().y + 1.0f));
		m_vecEnemyStartPos.push_back(glm::vec2(17.0f, m_pGround->GetPos().y + 1.0f));

		// Create enemy object instances
		for (GLuint i = 0; i < m_vecEnemyStartPos.size(); ++i)
		{
			CEnemy* pEnemy = new CEnemy(i, m_vecEnemyStartPos[i], glm::vec2(0.5f));
			pEnemy->SetDensity(0.5f);
			pEnemy->Init(*m_pWorld);
			m_vecEnemies.push_back(pEnemy);
		}
	}
	break;
	default:break;
	}

	// Set up the slingshot
	m_pSlingshotBase = new CSprite(glm::vec2(-20.0f, m_pGround->GetPos().y + 2.3f), glm::vec2(0.5f, 2.0f));
	m_pSlingshotBase->SetSprite(CUtility::GetInstance().ksSpriteSlingshotBase.c_str());
	m_pSlingshotBase->Init();
	m_pSlingshotBase->SetScale(glm::vec2(2.0f));
	m_v2SlingshotCenter = b2Vec2(m_pSlingshotBase->GetPos().x - 0.25f, m_pSlingshotBase->GetPos().y + 1.75f);

	m_pSlingshotArm = new CSprite(glm::vec2(m_pSlingshotBase->GetPos().x - 0.5f, m_pGround->GetPos().y + 3.25f), glm::vec2(0.5f, 2.0f));
	m_pSlingshotArm->SetSprite(CUtility::GetInstance().ksSpriteSlingshotArm.c_str());
	m_pSlingshotArm->Init();
	m_pSlingshotArm->SetScale(glm::vec2(1.35f));

	// Set the starting position of the birds
	m_vecBirdStartPos.push_back(glm::vec2(m_v2SlingshotCenter.x, m_v2SlingshotCenter.y));
	m_vecBirdStartPos.push_back(glm::vec2(m_v2SlingshotCenter.x - 1.0f, m_pGround->GetPos().y + 1.0f));
	m_vecBirdStartPos.push_back(glm::vec2(m_v2SlingshotCenter.x - 2.0f, m_pGround->GetPos().y + 1.0f));

	// Set up the three birds (regular, boost, and divebomber)
	for (GLuint i = 0; i < m_vecBirdStartPos.size(); ++i)
	{
		std::string sFilepath = "Resources/Art/Players/" + std::to_string(i) + ".png";
		CBird* pBird = new CBird(m_vecBirdStartPos[i], glm::vec2(0.5f), static_cast<EBirdType>(i + 1));
		pBird->SetSprite(sFilepath.c_str());
		pBird->Init(*m_pWorld);
		if (i != 0)
		{
			pBird->GetBody()->SetActive(false);
		}
		
		m_vecBirds.push_back(pBird);
	}
	
	// Set up score and score label
	m_uiScore = 0;
	m_tScoreLabel = new TextLabel("Score: " + std::to_string(m_uiScore), "Resources/Fonts/Orbitron-Bold.ttf", glm::vec2(CUtility::GetInstance().fScrWidth * 0.8f, CUtility::GetInstance().fScrHeight * 0.85f));
	m_tScoreLabel->SetScale(0.5f);
	m_tScoreLabel->SetColor(glm::vec3(1.0f, 1.0f, 0.2f));

	m_bDebugMode = false;

	Sleep(5);
}

// Remove any existing game entities to clear the way for restarting or quitting
void CGame::ClearGameEntities()
{
	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_pContactListener;
	m_pContactListener = nullptr;

	delete m_pSeesaw;
	m_pSeesaw = nullptr;

	delete m_pWreckingBall;
	m_pWreckingBall = nullptr;

	delete m_pWreckingBallPole;
	m_pWreckingBallPole = nullptr;

	delete m_pPulleySystem;
	m_pPulleySystem = nullptr;

	for (GLuint i = 0; i < m_vecEnemies.size(); i++)
	{
		delete m_vecEnemies[i];
		m_vecEnemies[i] = 0;
	}
	m_vecEnemies.clear();
	m_vecEnemyStartPos.clear();

	m_vecPlankAttribs.clear();

	for (GLuint i = 0; i < m_vecPlanks.size(); i++)
	{
		delete m_vecPlanks[i];
		m_vecPlanks[i] = nullptr;
	}
	m_vecPlanks.clear();

	delete m_pBackground;
	m_pBackground = nullptr;

	delete m_pSlingshotBase;
	m_pSlingshotBase = nullptr;

	delete m_pSlingshotArm;
	m_pSlingshotArm = nullptr;

	for (GLuint i = 0; i < m_vecBirds.size(); i++)
	{
		delete m_vecBirds[i];
		m_vecBirds[i] = nullptr;
	}
	m_vecBirds.clear();
	m_vecBirdStartPos.clear();

	delete m_pGround;
	m_pGround = nullptr;

	delete m_tScoreLabel;
	m_tScoreLabel = nullptr;
}

void CGame::CheckForBirdDeath()
{
	// If there are still available birds
	if (m_vecBirds.size() > 0)
	{
		// Check to see whether bird has run out of health
		CUserData* pBirdData = (CUserData*)m_vecBirds[0]->GetBody()->GetUserData();
		bool bInsufficientHealth = pBirdData->m_fHealth <= 0.0f;

		// Check to see if bird has gone outside of the left or right screen borders
		bool bOutsideBounds = (m_vecBirds[0]->GetPos().x > m_fScreenBorder) || (m_vecBirds[0]->GetPos().x < -(m_fScreenBorder));

		// If the bird is active (ie Has been fired from slingshot) and has either run out of health or gone out of bounds
		if (m_vecBirds[0]->GetIsActive() && (bInsufficientHealth || bOutsideBounds))
		{
			// Remove the bird from the world and destroy the bird instance
			m_pWorld->DestroyBody(m_vecBirds[0]->GetBody());
			delete m_vecBirds[0];
			m_vecBirds[0] = nullptr;
			m_vecBirds.erase(m_vecBirds.begin());

			// If there are still birds left to shoot
			if (m_vecBirds.size() > 0)
			{
				// Load the next bird in to the slingshot
				m_vecBirds[0]->GetBody()->SetTransform(m_v2SlingshotCenter, 0.0f);
				m_vecBirds[0]->GetBody()->SetActive(true);
				m_bIsBirdShootable = false;
				m_bIsBirdSelectable = false;
			}
		}
	}
}

void CGame::CheckForBirdEffects()
{
	if (m_vecBirds[0]->GetType() == BIRD_BOOST)
	{
		// If the player clicks the right mouse button
		if (CInput::GetInstance().GetMouseState(2) == INPUT_FIRST_PRESS && !m_bBoostUsed)
		{
			// Take the bird's current velocity and scale it by the boost factor
			b2Vec2 v2Velocity = m_vecBirds[0]->GetBody()->GetLinearVelocity();
			v2Velocity *= CUtility::GetInstance().kfBirdBoostFactor;
			m_vecBirds[0]->GetBody()->SetLinearVelocity(v2Velocity);
		}
	}
	else if (m_vecBirds[0]->GetType() == BIRD_DIVEBOMB)
	{
		// If the player clicks the right mouse button
		if (CInput::GetInstance().GetMouseState(2) == INPUT_FIRST_PRESS && !m_bBoostUsed)
		{
			// Take the bird's current velocity, remove the x component, and add negative y 
			// to shoot the bird downwards
			b2Vec2 v2Velocity = m_vecBirds[0]->GetBody()->GetLinearVelocity();
			v2Velocity.x = 0.0f;
			v2Velocity.y = -(CUtility::GetInstance().kfBirdDivebombFactor);
			m_vecBirds[0]->GetBody()->SetLinearVelocity(v2Velocity);
		}
	}
}

void CGame::CheckForSlingshotFiring(float _fDelta)
{
	// If the current bird in the slingshot has not been shot yet
	if (!m_vecBirds[0]->GetIsActive())
	{
		// Get the current position of the mouse
		b2Vec2 v2MousePos = b2Vec2(
			(CInput::GetInstance().GetMousePos().x * CUtility::GetInstance().fScrWidth) / m_fPixelToMetre,
			(CInput::GetInstance().GetMousePos().y * CUtility::GetInstance().fScrHeight) / m_fPixelToMetre
		);

		// If the mouse is hovering within range of the player (set to be the player size + a 30% overlap)
		b2Vec2 v2BirdPos = m_vecBirds[0]->GetBody()->GetPosition();
		float fDistance = b2Distance(v2MousePos, v2BirdPos);
		if (fDistance < (m_vecBirds[0]->GetSize().x * (CUtility::GetInstance().fScrWidth / m_fPixelToMetre)))
		{
			// And the player clicks the left mouse button
			if (CInput::GetInstance().GetMouseState(0) == INPUT_FIRST_PRESS)
			{
				// Make the bird selectable
				m_bIsBirdSelectable = true;
			}
		}

		// If the left mouse button is held down
		if (CInput::GetInstance().GetMouseState(0) == INPUT_HOLD)
		{
			if (m_bIsBirdSelectable)
			{
				// Set the slingshot radius to be 0.25% of the current screen width (allows for consistent results from multiple screen sizes)
				float fSlingshotRadius = (CUtility::GetInstance().fScrWidth * CUtility::GetInstance().kfSlingshotRadRatio);

				// If the position of the mouse falls outside the designated slingshot radius
				if (b2Distance(v2MousePos, m_v2SlingshotCenter) > fSlingshotRadius)
				{
					// Calculate the path between the center of the slingshot and the current mouse position
					b2Vec2 v2MaxDist = v2MousePos - m_v2SlingshotCenter;

					// Shift the player position along the path above until it falls on the perimeter of the slingshot radius
					v2MaxDist.Normalize();
					v2MaxDist *= fSlingshotRadius;
					m_vecBirds[0]->GetBody()->SetTransform(m_v2SlingshotCenter + (v2MaxDist), 0.0f);
				}
				else
				{
					// Otherwise set the birds position to the current mouse position
					m_vecBirds[0]->GetBody()->SetTransform(v2MousePos, 0.0f);
				}
			}
		}

		// If the left mouse button is released
		if (CInput::GetInstance().GetMouseState(0) == INPUT_FIRST_RELEASE)
		{
			// If the bird is not pulled out far enough
			if (b2Distance(v2MousePos, m_v2SlingshotCenter) < CUtility::GetInstance().fScrWidth * 0.001f)
			{
				// Set the birds position back to the center of the slingshot
				m_vecBirds[0]->GetBody()->SetTransform(m_v2SlingshotCenter, 0.0f);
				m_bIsBirdShootable = false;
			}
			else
			{
				m_bIsBirdShootable = true;
			}
		}

		if (CInput::GetInstance().GetMouseState(0) == INPUT_RELEASED)
		{
			// If the bird is in a valid position to be shot
			if (m_bIsBirdShootable)
			{
				// Mark the bird as being shot
				m_vecBirds[0]->SetIsActive(true);

				// Create a vector counter to the strength and direction that the bird has been pulled
				// (The further the bird is pulled back, the greater the force)
				b2Vec2 v2ImpulseDir = (m_fImpulseScalar * (m_v2SlingshotCenter - m_vecBirds[0]->GetBody()->GetPosition()));

				// Apply this as a force to shoot the bird through the center of the slingshot
				m_vecBirds[0]->GetBody()->ApplyLinearImpulseToCenter(v2ImpulseDir, true);
			}
			else
			{
				// Otherwise set the birds position back to the center of the slingshot
				m_vecBirds[0]->GetBody()->SetTransform(m_v2SlingshotCenter, 0.0f);
			}
		}
	}
}

// Used to kill off a bird if it slows down to the point of being idle
void CGame::CheckForBirdSlowdown()
{
	float fBirdXVelocity = m_vecBirds[0]->GetBody()->GetLinearVelocity().x;
	CUserData* pBirdData = (CUserData*)m_vecBirds[0]->GetBody()->GetUserData();

	// If the bird has been launched and its horizontal velocity is less than the slowdown threshold
	if (glm::abs(fBirdXVelocity < CUtility::GetInstance().kfBirdSlowdownThreshold) && m_vecBirds[0]->GetIsActive())
	{
		// Deduct some health from the bird
		pBirdData->m_fHealth -= CUtility::GetInstance().kfBirdSlowdownHealthPenalty;
	}
}

// Check if the player has met the conditions for a loss
void CGame::ProcessCheckForLoss()
{
	// If no birds are left to shoot and enemies still remain
	if (m_vecBirds.size() == 0 && m_vecEnemies.size() > 0)
	{
		// The player has lost the game
		m_eGameResult = RESULT_LOSE;
		m_bGameActive = false;
	}
}

// Check if the player has met the conditions for a win
void CGame::ProcessCheckForWin()
{
	// If no enemies remain
	if (m_vecEnemies.size() == 0)
	{
		// Add a bonus for any remaining birds to the player's score
		m_uiScore += CUtility::GetInstance().kuiBirdPoints * m_vecBirds.size();

		// Determine the strength of the player's win by comparing their score to the thresholds
		// and then set the appropriate game over result
		if (m_uiScore > CUtility::GetInstance().kuiScoreThresholds[2])
		{
			m_eGameResult = RESULT_WIN_OUTSTANDING;
		}
		else if (m_uiScore > CUtility::GetInstance().kuiScoreThresholds[1])
		{
			m_eGameResult = RESULT_WIN_GREAT;
		}
		else if (m_uiScore > CUtility::GetInstance().kuiScoreThresholds[0])
		{
			m_eGameResult = RESULT_WIN_GOOD;
		}

		m_bGameActive = false;
	}
}