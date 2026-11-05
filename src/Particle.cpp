#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3D position, Vector3D velocity, float mass, float damping,
	IntegratorType type): mass(mass), damping(damping), velocity(velocity),
	acceleration(0, 0, 0), transform(position), intg_type(type) { // TODO: calcular last_pos con EulerSemiImplícito, siguiente integración Verlet (bool firstIntegration?)
	// Creamos una esfera y un render item con dicha geometría
	item = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	item->shape->release(); // libera la referencia inicial de CreateShape; el RenderItem conserva la suya
}

Particle::~Particle() {
	item->release();
}

// Añade una fuerza (en newtons) al acumulador de fuerzas
void Particle::addForce(float force, Vector3D direction) { // TODO: a vector3D de force (incluye force + direction)
	acceleration += direction.normalize() * (force / mass); // aceleración = fuerza / masa
}


void Particle::update(double t) {
	// integrate
	switch (intg_type) {
	case IntegratorType::Euler: intg_euler(t); break;
	case IntegratorType::SemiEuler: intg_semiEuler(t); break;
	case IntegratorType::Verlet: intg_verlet(t); break;
	}

	acceleration = Vector3D(0, 0, 0); // restaurar acc a 0 (ya que las fuerzas se aplican en cada "step")
}

void Particle::intg_euler(double t) {
	// Euler (pos y luego vel)
	transform.p += velocity * t; // cambiamos la componente p (posición) de transform
	velocity += acceleration * t;
	velocity *= pow(damping, t); // aplicamos damping
}

void Particle::intg_semiEuler(double t) {
	// SemiEuler (vel y luego pos)
	velocity += acceleration * t;
	transform.p += velocity * t;
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
