#pragma once
#include "Particle.h"

class Projectile : public Particle {
protected:
	Vector3D gravity; // gravedad simulada del proyectil

public:
	Projectile(Vector3D position, Vector3D direction, float real_mass,
		Vector3D gravity, float sim_velocity, float real_velocity,
		physx::PxVec4 color = physx::PxVec4(1.f, 1.f, 1.f, 1.f), IntegratorType type = IntegratorType::SemiEuler);

	void update(double t, const std::vector<const ForceGenerator*>& force_generators = {}) override;
};
