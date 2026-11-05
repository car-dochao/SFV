#include "Particle.h"
#include "ForceGenerator.h"
#include <cmath>

Particle::Particle(Vector3D position, Vector3D velocity, float mass, float life, physx::PxVec4 color,
	IntegratorType type, float damping): mass(mass), damping(damping), position(position), velocity(velocity),
	acceleration(0, 0, 0), life(life), color(color), intg_type(type) {
}

// Añade una fuerza (en newtons) al acumulador de fuerzas
void Particle::addForce(Vector3D force) {
	acceleration += force / mass; // aceleración = fuerza / masa
}


void Particle::update(double t, const std::vector<const ForceGenerator*>& force_generators) {
	// la particula consulta las fuerzas; la lista pertenece al sistema, no a cada particula
	for (const ForceGenerator* force_generator : force_generators)
		addForce(force_generator->calculateForce(*this));

	// integrate
	switch (intg_type) {
	case IntegratorType::Euler: intg_euler(t); break;
	case IntegratorType::SemiEuler: intg_semiEuler(t); break;
	case IntegratorType::Verlet: intg_verlet(t); break;
	}

	acceleration = Vector3D(0, 0, 0); // restaurar acc a 0 (ya que las fuerzas se aplican en cada "step")
	life -= float(t);
}

void Particle::intg_euler(double t) {
	// Euler (pos y luego vel)
	position += velocity * t;
	velocity += acceleration * t;
	velocity *= pow(damping, t); // aplicamos damping
}

void Particle::intg_semiEuler(double t) {
	// SemiEuler (vel y luego pos)
	velocity += acceleration * t;
	position += velocity * t;
	velocity *= pow(damping, t); // aplicamos damping
}

void Particle::intg_verlet(double t) {
	// Verlet (nueva pos respecto la anterior y la aceleración)
	// TODO: queda por intergar primero con otro (bool integrated)
	// Vector3D position(transform.p);
	// transform.p = position + (position - last_pos) * damping + acceleration * t * t;
	// velocity = (transform.p - position) / t;
	// last_pos = position;
}
