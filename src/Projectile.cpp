#include "Projectile.h"

Projectile::Projectile(Vector3D position, Vector3D direction, float real_mass,
	Vector3D gravity, float sim_velocity, float real_velocity,
	physx::PxVec4 color, IntegratorType type) : 
    Particle(position, direction, real_mass, 0.f, color, type) {
	// aplicamos la dirección normalizada a la velocidad (simulada)
	velocity = direction.normalize() * sim_velocity;

	// masa y gravedad simuladas
	mass = real_mass * (real_velocity * real_velocity) / (sim_velocity * sim_velocity);
	this->gravity = gravity * (sim_velocity * sim_velocity) / (real_velocity * real_velocity);
}

void Projectile::update(double t, const std::vector<const ForceGenerator*>& force_generators) {
    
	acceleration += gravity;
	
	Particle::update(t, force_generators); // integra la partícula
}
