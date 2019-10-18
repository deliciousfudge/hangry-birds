//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: utils.h
// Description	: CUtility header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <Box2D/Box2D.h>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes

class CUtility
{
	// Member methods
public:
	~CUtility();

	// Singleton Methods
	static CUtility& GetInstance();
	static void DestroyInstance();

private:
	CUtility();

	// Member variables
public:
	// Screen Resolution
	float fScrWidth{ 1280.0f };
	float fScrHeight{ 720.0f };

	// Physics
	b2Vec2 kv2Gravity = b2Vec2(0.0f, -0.14f); // Regular gravity (9.8ms) then divided by pixel:metre ratio of 70:1
	float kfTimestep = 1.0f / 40.0f; 
	GLuint kuiVelocityIters{ 8 };
	GLuint kuiPositionIters{ 3 };

	// Sprite filepaths
	std::string ksSpriteEnemy0 = "Resources/Art/Food/47.png";
	std::string ksSpriteEnemy1 = "Resources/Art/Food/48.png";
	std::string ksSpriteEnemy2 = "Resources/Art/Food/49.png";
	std::string ksSpriteSlingshotBase = "Resources/Art/SlingshotBase.png";
	std::string ksSpriteSlingshotArm = "Resources/Art/SlingshotArm.png";
	std::string ksSpriteSeesawBase = "Resources/Art/Food/5.png";
	std::string ksSpriteSeesawBoard = "Resources/Art/Tiles/cakeMid.png";
	std::string ksSpriteWreckingTether = "Resources/Art/Tiles/lollipopBaseBeige.png";
	std::string ksSpriteWreckingPole = "Resources/Art/Food/50.png";
	std::string ksSpriteWreckingBall = "Resources/Art/Food/46.png";
	std::string ksSpritePlankBreakable = "Resources/Art/Tiles/cakeMid.png";
	std::string ksSpritePlankUnbreakable = "Resources/Art/Tiles/chocoMid.png";
	std::string ksSpriteGround = "Resources/Art/Tiles/cakeHalfAltMid.png";
	std::string ksSpriteMenuBackground = "Resources/Art/stars.png";
	std::string ksSpritePulleyGear = "Resources/Art/Food/23.png";
	std::string ksSpritePulleyTarget = "Resources/Art/target.png";
	std::string ksSpritePulleyWeight = "Resources/Art/Food/33.png";
	std::string ksSpriteBackgroundLevel1 = "Resources/Art/level1background.png";
	std::string ksSpriteBackgroundLevel2 = "Resources/Art/level2background.png";

	// Entity health
	float kfHealthBreakablePlank{ 2.0f };
	float kfHealthBird{ 5.0f };
	float kfHealthEnemy{ 7.5f };

	// Damage
	float kfDamageBirdHeavy{ 15.0f };
	float kfDamageBirdOther{ 5.0f };
	float kfDamageWreckingBall{ 5.0f };

	// Other
	GLuint kuiStartingLevel = 1;
	float kfSlingshotRadRatio = 0.0025f; // Proportion of the screen width to set the slingshot radius as (default 0.25%)
	float kfBirdBoostFactor = 2.0f;
	float kfBirdDivebombFactor = 5.0f;
	float kfMouseSensitivity = 0.2f;

	// Scoring
	GLuint kuiScoreThresholds[3] = { 12000, 20000, 25000 };
	GLuint kuiBirdPoints = 10000;
	GLuint kuiEnemyPoints = 2500;
	GLuint kuiPlankPoints = 1000;

	float kfBirdSlowdownThreshold = 0.01f;
	float kfBirdSlowdownHealthPenalty = 0.05f;

protected:
	static CUtility* s_pUtility;
};