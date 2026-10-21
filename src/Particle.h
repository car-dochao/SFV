#pragma once

#include "Vector3D.h"
#include "RenderUtils.hpp"

class Particle {

protected:

	float mass;
	float damping;

	Vector3D velocity;
	Vector3D acceleration;

	physx::PxTransform transform; // position & quaternion

public:
	enum class IntegratorType { Euler, SemiEuler, Verlet };

	Particle(Vector3D position, Vector3D velocity, float mass = 1.f, float damping = 0.98f,
		IntegratorType type = IntegratorType::Euler);

	virtual ~Particle();

	virtual void update(double t);
	virtual void addForce(float force, Vector3D direction);

private:
	RenderItem* item;

	IntegratorType intg_type; // por defecto Euler (ctra)

	// métodos para cada tipo de integrador
	void intg_euler(double t);
	void intg_semiEuler(double t);
	void intg_verlet(double t);

	// para verlet
	bool integrated;
	Vector3D last_pos;
};
