// Fill out your copyright notice in the Description page of Project Settings.

#include "Spring.h"
#include "spring_mass.h"

Spring::Spring(MassPoint* m1, MassPoint* m2, float length) :
m_m1(m1), m_m2(m2), 
m_spring_length_init(length),
m_stiffness(0.1),
m_damper(0.001)
{
}

Spring::~Spring()
{
}


void
Spring::Tick()
{	
	//01 Normalize the vector: Dist_m1m2_nor = (m2 - m1) / |m2 - m1|
	FVector m1m2 = m_m2-> m_currPos - m_m1->m_currPos;
	float Dist_m1m2 = FVector::Dist(m_m2->m_currPos, m_m1->m_currPos);
	FVector Dist_m1m2_nor = m1m2 / Dist_m1m2;

	//02 Calculate the spring force：F_s = k_s * (|m2 - m1| - L) * Dist_m1m2_nor
	FVector F_s = m_stiffness * (Dist_m1m2 - m_spring_length_init) * Dist_m1m2_nor;

	//03 Calculate the dramper force: F_d = -k_d * (dotProduct((v1 - v2),Dist_m1m2_nor)) * Dist_m1m2_nor
	FVector Vel_m1m2 = m_m1->m_velocity - m_m2->m_velocity;
	FVector F_d = - m_damper * (FVector::DotProduct( Vel_m1m2, Dist_m1m2_nor)) * Dist_m1m2_nor;

	//04 Calculate the total force: F = F_s + F_d
	FVector F_toltal = F_s + F_d;

	//05 Apply the force to the mass points
	m_m1->addForce(F_toltal);
	m_m2->addForce(-F_toltal);

}
