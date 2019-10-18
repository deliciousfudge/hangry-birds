//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: entity.cpp
// Description	: Controls entity implementation logic
// Author		: Roger Smith
// Mail			: roger.smi7429@mediadesign.school.nz

// Library Includes

// Local Includes

// This include
#include "entity.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEntity::CEntity(glm::vec2 _v2Pos, glm::vec2 _v2Size, int _iSpanX, int _iSpanY, int _iNumSpr)
	: CSprite(_v2Pos, _v2Size, _iSpanX, _iSpanY, _iNumSpr)
	, m_bFacingRight(true)
	, m_ePhysicsBody(BODY_STATIC)
	, m_ePhysicsShape(SHAPE_POLYGON)
{

}

CEntity::~CEntity()
{
	delete m_pUserData;
	m_pUserData = nullptr;

	delete m_pBodyDef;
	m_pBodyDef = nullptr;

	delete m_pPolyShape;
	m_pPolyShape = nullptr;

	delete m_pCircleShape;
	m_pCircleShape = nullptr;

	delete m_pTriangleShape;
	m_pTriangleShape = nullptr;

	//delete m_pBody;
	//m_pBody = nullptr;

	delete m_pFixtureDef;
	m_pFixtureDef = nullptr;

	m_v2DebugVerts.clear();
	m_uiDebugIndices.clear();
}

void CEntity::Init(b2World& _rWorld)
{
	m_pUserData = new CUserData(m_eEntityType, m_fHealth);

	// Init Physics
	{
		// Create a body definition and set the position of the tile
		m_pBodyDef = new b2BodyDef();

		// Physics bodies are static by default, so only need to specify type if it is dynamic
		if (m_ePhysicsBody == BODY_DYNAMIC) { m_pBodyDef->type = b2_dynamicBody; }
		
		m_pBodyDef->position.Set(m_v2Pos.x, m_v2Pos.y);
		m_pBodyDef->linearDamping = m_fLinearDamping;
		m_pBodyDef->angularDamping = m_fAngularDamping;
		m_pBodyDef->userData = m_pUserData;

		// Create a static body for the player character by passing the body definition to the world object
		m_pBody = _rWorld.CreateBody(m_pBodyDef);
		m_pBody->SetTransform(m_pBody->GetPosition(), m_v3Rot.z);

		if (m_ePhysicsShape == SHAPE_POLYGON)
		{
			m_pPolyShape = new b2PolygonShape();
			m_pPolyShape->SetAsBox(m_v2Size.x, m_v2Size.y);
			m_uiCount = m_pPolyShape->m_count;
		}
		else if (m_ePhysicsShape == SHAPE_CIRCLE)
		{
			m_pCircleShape = new b2CircleShape();
			m_pCircleShape->m_radius = m_v2Size.x;
		}
		else if (m_ePhysicsShape == SHAPE_TRIANGLE)
		{
			m_pTriangleShape = new b2PolygonShape();
			
			b2Vec2 v2Verts[3];
			v2Verts[0].Set(-1.0f, -1.0f);
			v2Verts[1].Set(0.0f, 1.0f);
			v2Verts[2].Set(1.0f, -1.0f);
			m_pTriangleShape->Set(v2Verts, 3);

			m_uiCount = m_pTriangleShape->m_count;
		}

		// Beef up the size of the sprites to match the size of their physics counterparts (given that Box2D uses half sizes to set up physics entities)
		SetScale(glm::vec2(2.0f));

		if (m_ePhysicsBody == BODY_DYNAMIC)
		{
			// Use the newly created shape to create a new fixture definition
			m_pFixtureDef = new b2FixtureDef;

			if (m_ePhysicsShape == SHAPE_POLYGON)
			{
				m_pFixtureDef->shape = m_pPolyShape;
				m_fDensity = 0.2f;
				m_fFriction = 0.1f;
			}
			else if (m_ePhysicsShape == SHAPE_CIRCLE)
			{
				m_pFixtureDef->shape = m_pCircleShape;
				m_fRestitution = 0.5f;
				m_fDensity = 0.85f;
				m_fFriction = 1.0f;
			}
			else if (m_ePhysicsShape == SHAPE_TRIANGLE)
			{
				m_pFixtureDef->shape = m_pTriangleShape;
				m_fDensity = 0.85f;
				m_fFriction = 0.2f;
			}

			m_pFixtureDef->density = m_fDensity;
			m_pFixtureDef->friction = m_fFriction;
			m_pFixtureDef->restitution = m_fRestitution;

			// Attach this new fixture definition to the player character's physics body to create a dynamic body
			m_pBody->CreateFixture(m_pFixtureDef);
		}
		else if (m_ePhysicsBody == BODY_STATIC)
		{
			// Use a shortcut to create a static body (since we don't need to supply things like friction)
			if (m_ePhysicsShape == SHAPE_POLYGON)
			{
				m_pBody->CreateFixture(m_pPolyShape, 0.0f);
			}
			else if (m_ePhysicsShape == SHAPE_CIRCLE)
			{
				m_pBody->CreateFixture(m_pCircleShape, 0.0f);
			}
			else if (m_ePhysicsShape == SHAPE_TRIANGLE)
			{
				m_pBody->CreateFixture(m_pTriangleShape, 0.0f);
			}
		}
	}

	// Init Debug Draw capability
	{
		m_uiDebugProgram = CResourceLoader::GetInstance().CreateProgram("Resources/Shaders/Debug.vs", "Resources/Shaders/Debug.fs");

		if (m_ePhysicsShape == SHAPE_POLYGON)
		{
			m_v2DebugVerts.push_back(b2Vec2(-m_v2Size.x, m_v2Size.y)); // Top Left
			m_v2DebugVerts.push_back(b2Vec2(m_v2Size.x, m_v2Size.y)); // Top Right
			m_v2DebugVerts.push_back(b2Vec2(m_v2Size.x, -m_v2Size.y)); // Bottom Right
			m_v2DebugVerts.push_back(b2Vec2(-m_v2Size.x, -m_v2Size.y)); // Bottom Left

			m_uiDebugIndices.push_back(0);
			m_uiDebugIndices.push_back(1);
			m_uiDebugIndices.push_back(2);
			m_uiDebugIndices.push_back(0);
			m_uiDebugIndices.push_back(2);
			m_uiDebugIndices.push_back(3);
		}
		else if (m_ePhysicsShape == SHAPE_CIRCLE)
		{
			int num_segments = 360;
			float angleOffset = 180.0f / 3.1415926f;

			for (int i = 0; i < num_segments; i++)
			{
				float angle = (i / 3) * (3.1415926f / 180.0f);
				b2Vec2 v2Vert;
				v2Vert.x = m_v2Size.x * glm::cos(angle) + m_v2Pos.x; //calculate the x component 
				v2Vert.y = m_v2Size.y * glm::sin(angle) + m_v2Pos.y; //calculate the y component 

				m_v2DebugVerts.push_back(v2Vert);
			}

			for (int i = 0; i < num_segments; ++i)
			{
				m_uiDebugIndices.push_back(i);
			}
		}
		else if (m_ePhysicsShape == SHAPE_TRIANGLE)
		{
			m_v2DebugVerts.push_back(b2Vec2(0.0f, m_v2Size.y)); // Top
			m_v2DebugVerts.push_back(b2Vec2(-m_v2Size.x, -m_v2Size.y)); // Bottom Left
			m_v2DebugVerts.push_back(b2Vec2(m_v2Size.x, -m_v2Size.y)); // Bottom Right

			m_uiDebugIndices.push_back(0);
			m_uiDebugIndices.push_back(1);
			m_uiDebugIndices.push_back(2);
		}

		glGenVertexArrays(1, &m_uiDebugVAO);
		glBindVertexArray(m_uiDebugVAO);

		GLuint debugVBO;
		glGenBuffers(1, &debugVBO);
		glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
		glBufferData(GL_ARRAY_BUFFER, m_v2DebugVerts.size() * sizeof(b2Vec2), &m_v2DebugVerts[0], GL_STATIC_DRAW);

		glCullFace(GL_BACK); // Cull the Back faces 
		glFrontFace(GL_CW); // Front face is Clockwise order 
		glEnable(GL_CULL_FACE); // Turn on the back face culling

		glVertexAttribPointer
		(
			0, // Layout location on vertex shader 
			2, // 3 float components (eg position) 
			GL_FLOAT, // Type of data 
			GL_FALSE, // Data normalized? 
			2 * sizeof(GLfloat), // Stride of the single vertex(pos.x and pos.y) 
			(GLvoid*)(0) // Offset from beginning of Vert
		);
		glEnableVertexAttribArray(0);

		GLuint debugEBO;
		glGenBuffers(1, &debugEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, debugEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_uiDebugIndices.size() * sizeof(GLuint), &m_uiDebugIndices[0], GL_STATIC_DRAW);
	}
	
	CSprite::Init();
}

void CEntity::Update(GLfloat _fDelta)
{
	if (m_pBody != nullptr)
	{
		m_v2Pos.x = m_pBody->GetPosition().x;
		m_v2Pos.y = m_pBody->GetPosition().y;
		m_v3Rot.z = m_pBody->GetAngle();
	}

	CSprite::Update(_fDelta);
}

void CEntity::Render(bool _bDebugMode)
{
	if (_bDebugMode)
	{
		glm::vec3 objPosition = glm::vec3(m_v2Pos, 0.0f);

		glm::mat4 m_m4Translate = glm::translate(glm::mat4(), objPosition);
		glm::mat4 m_m4Scale = glm::scale(glm::mat4(), glm::vec3(1.0f));
		glm::mat4 m_m4Rotate = glm::rotate(glm::mat4(), m_v3Rot.x, glm::vec3(1, 0, 0));
		m_m4Rotate = glm::rotate(m_m4Rotate, m_v3Rot.y, glm::vec3(0, 1, 0));
		m_m4Rotate = glm::rotate(m_m4Rotate, m_v3Rot.z, glm::vec3(0, 0, 1));

		// Model matrix to store transformations
		glm::mat4 m_m4Model = m_m4Translate * m_m4Rotate * m_m4Scale;

		glUseProgram(m_uiDebugProgram);

		glm::mat4 MVP = CCamera::GetInstance().GetProjectionMatrix() * CCamera::GetInstance().GetViewMatrix() * m_m4Model;

		GLuint MVPLoc = glGetUniformLocation(m_uiDebugProgram, "MVP");
		glUniformMatrix4fv(MVPLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		glBindVertexArray(m_uiDebugVAO); // Bind VAO

		glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0); // Unbind VAO
	}
	else
	{
		CSprite::Render();
	}
}

bool CEntity::GetFacingRight() const
{
	return m_bFacingRight;
}

void CEntity::SetFacingRight(bool _bFacingRight)
{
	m_bFacingRight = _bFacingRight;
}

b2Body* CEntity::GetBody() const
{
	return m_pBody;
}

void CEntity::SetPhysicsBody(EPhysicsBody _eBody)
{
	m_ePhysicsBody = _eBody;
}

void CEntity::SetPhysicsShape(EPhysicsShape _eShape)
{
	m_ePhysicsShape = _eShape;
}

void CEntity::SetDensity(float _fDensity)
{
	m_fDensity = _fDensity;
}

void CEntity::SetRestitution(float _fRestitution)
{
	m_fRestitution = _fRestitution;
}

void CEntity::SetFriction(float _fFriction)
{
	m_fFriction = _fFriction;
}

void CEntity::SetLinearDamping(float _fLinearDamping)
{
	m_fLinearDamping = _fLinearDamping;
}

void CEntity::SetAngularDamping(float _fAngularDamping)
{
	m_fAngularDamping = _fAngularDamping;
}

void CEntity::SetEntityType(EEntityType _eEntityType)
{
	m_eEntityType = _eEntityType;
}

b2Shape* CEntity::GetShape() const
{
	if (m_ePhysicsShape == SHAPE_POLYGON)
	{
		return m_pPolyShape;
	}
	else if (m_ePhysicsShape == SHAPE_CIRCLE)
	{
		return m_pCircleShape;
	}
	else if (m_ePhysicsShape == SHAPE_TRIANGLE)
	{
		return m_pTriangleShape;
	}
	else
	{
		return nullptr;
	}
}

void CEntity::ResetPos()
{
	SetPos(m_v2StartPos);
}
