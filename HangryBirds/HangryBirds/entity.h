//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: entity.h
// Description	: CEntity header file
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

#pragma once

// Library Includes
#include <Box2D/Box2D.h>
#include <vector>

// Local Includes
#include "sprite.h"
#include "input.h"
#include "userdata.h"

// Types
enum EPhysicsBody
{
	BODY_STATIC = 0,
	BODY_DYNAMIC = 1,
	BODY_KINEMATIC = 2,
};
enum EPhysicsShape
{
	SHAPE_POLYGON = 0,
	SHAPE_CIRCLE = 1,
	SHAPE_TRIANGLE = 2,
};

// Constants

// Prototypes

class CEntity : public CSprite
{
	// Member functions
public:
	CEntity(glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX = 1, int _iSpanY = 1, int _iNumSpr = 1);
	virtual ~CEntity();
	
	virtual void Init(b2World& _rWorld);
	virtual void Update(GLfloat _fDelta);
	virtual void Render(bool _bDebugMode);

	bool GetFacingRight() const;
	void SetFacingRight(bool _bFacingRight);

	b2Body* GetBody() const;

	void SetPhysicsBody(EPhysicsBody _eBody);
	void SetPhysicsShape(EPhysicsShape _eShape);

	void SetDensity(float _fDensity);
	void SetRestitution(float _fRestitution);
	void SetFriction(float _fFriction);
	void SetLinearDamping(float _fLinearDamping);
	void SetAngularDamping(float _fAngularDamping);

	void SetEntityType(EEntityType _eEntityType);
	
	b2Shape* GetShape() const;

	void ResetPos();

	// Member variables
protected:
	bool m_bFacingRight;
	bool m_bDebugMode;

	b2BodyDef* m_pBodyDef;
	b2PolygonShape* m_pPolyShape;
	b2CircleShape* m_pCircleShape;
	b2PolygonShape* m_pTriangleShape;
	b2Body* m_pBody;
	b2FixtureDef* m_pFixtureDef;

	EPhysicsBody m_ePhysicsBody;
	EPhysicsShape m_ePhysicsShape;

	float m_fDensity{ 1.0f };
	float m_fRestitution{ 0.0f };
	float m_fFriction{ 0.5f };
	float m_fLinearDamping{ 0.0f };
	float m_fAngularDamping{ 0.0f };

	EEntityType m_eEntityType;
	GLfloat m_fHealth{ 1000.0f };

	CUserData* m_pUserData;

private:
	GLuint m_uiDebugVAO;
	GLuint m_uiDebugProgram;
	std::vector<b2Vec2> m_v2DebugVerts;
	std::vector<GLuint> m_uiDebugIndices;
	GLuint m_uiCount;
};
