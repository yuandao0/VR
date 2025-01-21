// Fill out your copyright notice in the Description page of Project Settings.

#include "MassPoint.h"
#include "spring_mass.h"
#include "Math/UnrealMathUtility.h"


MassPoint::MassPoint(uint32 vertex_id, bool movable, FVector pos) :
m_vertex_id(vertex_id),
m_currPos(pos),
m_prevPos(pos),
m_force(FVector::ZeroVector),
m_velocity(FVector::ZeroVector),
m_movable(movable),
m_mass(0.00005)
{
}

void
MassPoint::updateGravity()
{
	// FIXME: gravity
	//01 Calculate the gravity: F_gravity = m * g
	FVector F_gravity = FVector(0, 0, m_mass * -9.8);

	//02 Add a random vector offset
	float Offset_range = 0.001;
	float x = FMath::RandRange(-Offset_range, Offset_range);
	float y = FMath::RandRange(-Offset_range, Offset_range);
	float z = FMath::RandRange(-Offset_range, Offset_range);
	FVector Offset = FVector(x, y, z);

	//03 Apply the gravity
	addForce(F_gravity + Offset);
}

void 
MassPoint::updateCurPos(float deltaT)
{
	if (m_movable)
	{
		// FIXME: Verlet
		//m_velocity += m_force / m_mass * deltaT;
		//m_currPos += m_velocity * deltaT;
		
		m_prevPos = m_currPos;

		// Verlet intergration: x(t+1) = 2*x(t) - x(t-1) + a(t) * dt^2
		m_currPos = 2 * m_currPos - m_prevPos + (m_force/ m_mass) * deltaT * deltaT;
		m_prevPos = m_currPos;
	}
	m_force = FVector::ZeroVector;
}

void
MassPoint::addForce(FVector f)
{
	if (m_movable)
	{
		m_force += f;
	}
}

MassPoint::~MassPoint()
{
}
