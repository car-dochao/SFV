#include "ParticleSystems.h"
#include "RenderUtils.hpp"
#include "Render/Render.h"

ParticleSystem::ParticleSystem(Vector3D position, float pos_deviation, Vector3D velocity, float vel_deviation,
    float lifetime, Vector4 color, Vector3D gravity) : shape(CreateShape(physx::PxSphereGeometry(0.15f))), position(position), velocity(velocity), color(color),
    lifetime(lifetime), gravity(gravity), position_dist(0.f, pos_deviation), velocity_dist(0.f, vel_deviation) {
}

ParticleSystem::~ParticleSystem() {
    shape->release();
}

void ParticleSystem::update(float dt) {
    // recorremos el array hasta la ultima particula viva
    for (int i = actives; i > 0; --i) {
        Particle& p = particles[i - 1]; // pillamos la dir a mem de la particula viva segun i

        // Integramos la particula, Semi Euler (TODO: hacer posible integrar con otras opciones?)
        p.velocity += gravity * dt;
        p.position += p.velocity * dt;
        p.life -= dt;

        // si la particula "viva" esta muerta la cambiamos por la ultima viva
        if (p.life <= 0.f) {
            --actives;
            p = particles[actives];
        }
    }

    // emitimos una nueva particula (usando la primera de las muertas)
    emmitParticle();
}

// emite una particula usando una marcada como muerta (si la hay vaya)
void ParticleSystem::emmitParticle() {
    if (actives < MAX_PARTICLES) {
        Particle& p = particles[actives];

        // media + ruido de la distribucion en cada eje
        p.position = position + Vector3D(position_dist(generator), position_dist(generator), position_dist(generator));
        p.velocity = velocity + Vector3D(velocity_dist(generator), velocity_dist(generator), velocity_dist(generator));
        p.life = lifetime;
        ++actives;
    }
}

void ParticleSystem::render() const {
    for (int i = 0; i < actives; ++i)
        renderShape(*shape, physx::PxTransform(particles[i].position), color);
}
