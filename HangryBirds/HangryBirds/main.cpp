#include <glew\glew.h>
#include <freeglut\freeglut.h>
#include <FMOD\fmod.hpp>
#include <Box2D/Box2D.h>

#include "resourceloader.h"
#include "scenemanager.h"
#include "input.h"
#include "utils.h"
#include "TextLabel.h"

// Prototypes
void Init();
void Render();
void Update();
void KeyBoardDown(unsigned char _ucKey, int _iX, int _iY);
void KeyBoardUp(unsigned char _ucKey, int _iX, int _iY);
void Mouse(int _iButton, int _iGlutState, int _iX, int _iY);
void MousePassiveMovement(int _iX, int _iY);
void CleanUp();

GLuint program;
GLfloat g_fDeltaTime = 0.0f;
GLfloat g_fLastTick = 0.0f;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300, 10);
	glutInitWindowSize(static_cast<int>(CUtility::GetInstance().fScrWidth), static_cast<int>(CUtility::GetInstance().fScrHeight));
	glutCreateWindow("Hangry Birds");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewInit();
	Init();
	
	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutKeyboardFunc(KeyBoardDown);
	glutKeyboardUpFunc(KeyBoardUp);
	glutMouseFunc(Mouse);
	glutPassiveMotionFunc(MousePassiveMovement);
	glutMotionFunc(MousePassiveMovement);

	glutIgnoreKeyRepeat(1);

	glutCloseFunc(CleanUp);

	glutMainLoop();		// Must be the last glut line called

	return(0);
}

void Init()
{
	CSceneManager::GetInstance().Init();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT); // Call this once before rendering all sprites

	CSceneManager::GetInstance().Render();

	glutSwapBuffers(); // Call this once after rendering all sprites
}

void Update()
{
	GLfloat fCurrentTick = static_cast<GLfloat>(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f; // Get current time
	g_fDeltaTime = fCurrentTick - g_fLastTick;
	g_fLastTick = fCurrentTick;

	GLint m_uiViewportSize[4];
	glGetIntegerv(GL_VIEWPORT, m_uiViewportSize);
	CUtility::GetInstance().fScrWidth = static_cast<float>(m_uiViewportSize[2]);
	CUtility::GetInstance().fScrHeight = static_cast<float>(m_uiViewportSize[3]);

	CSceneManager::GetInstance().Update(g_fDeltaTime);
	CCamera::GetInstance().Update();

	glutPostRedisplay();

	// This is placed last to check whether a given key state has recently changed and make the necessary adjustments
	CInput::GetInstance().Update();
}

void KeyBoardDown(unsigned char _ucKey, int _iX, int _iY)
{
	CInput::GetInstance().KeyBoardDown(_ucKey, _iX, _iY);
}

void KeyBoardUp(unsigned char _ucKey, int _iX, int _iY)
{
	CInput::GetInstance().KeyBoardUp(_ucKey, _iX, _iY);
}

void Mouse(int _iButton, int _iGlutState, int _iX, int _iY)
{
	CInput::GetInstance().Mouse(_iButton, _iGlutState, _iX, _iY);
}

void MousePassiveMovement(int _iX, int _iY)
{
	CInput::GetInstance().MousePassiveMovement(_iX, _iY);
}

void CleanUp()
{
	CInput::DestroyInstance();
	CSceneManager::DestroyInstance();
	CCamera::DestroyInstance();
	CUtility::DestroyInstance();
}