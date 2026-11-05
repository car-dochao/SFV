#pragma once

#include "Vector3D.h"
#include <vector>

class ForceGenerator;

class Particle {

protected:

	float mass = 1.f;
	float damping = 0.98f;

	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	float life = 0.f;
	physx::PxVec4 color{1.f, 1.f, 1.f, 1.f};

public:
	enum class IntegratorType { Euler, SemiEuler, Verlet };

	Particle() = default;
	Particle(Vector3D position, Vector3D velocity, float mass, float life,
		physx::PxVec4 color = physx::PxVec4(1.f, 1.f, 1.f, 1.f),
		IntegratorType type = IntegratorType::SemiEuler, float damping = 0.98f);

	virtual ~Particle() = default;

	virtual void update(double t, const std::vector<const ForceGenerator*>& force_generators = {});
	void addForce(Vector3D force);

	const Vector3D& getPosition() const { return position; }
	const Vector3D& getVelocity() const { return velocity; }
	float getMass() const { return mass; }
	float getLife() const { return life; }
	const physx::PxVec4& getColor() const { return color; }

private:
	IntegratorType intg_type = IntegratorType::SemiEuler; // por defecto SemiEuler (ctra)

	// métodos para cada tipo de integrador
	void intg_euler(double t);
	void intg_semiEuler(double t);
	void intg_verlet(double t);

	// para verlet
	bool integrated;
	Vector3D last_pos;
};
