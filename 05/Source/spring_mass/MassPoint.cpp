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
		
		//01 Calculate the acceleration with gamma
		FVector Acceleration = m_force / m_mass - 0.1 * m_velocity;

		//02 Calculate the new position
		FVector Temp = m_currPos;
		m_currPos = 2 * m_currPos - m_prevPos + Acceleration * deltaT * deltaT;
		m_prevPos = Temp;

		//03 Calculate the new velocity
		m_velocity = (m_currPos - m_prevPos) / deltaT;
		
		/*** Methd 2
		//01 Calculate the new position
		m_currPos += m_velocity * deltaT + 0.5 * Last_acceleration * deltaT * deltaT;

		//02 Calculate the new acceleration
		New_acceleration = m_force / m_mass;
		
		//03 Calculate the new velocity
		m_velocity += 0.5 * (Last_acceleration + New_acceleration) * deltaT;
		***/
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
