#include "ParticleSystem.h"
#include "RenderUtils.hpp"

#include <cmath>

// Ctra si el tipo de bounding es sphere (float radius)
ParticleSystem::ParticleSystem(Vector3D position, Vector3D velocityMean, Vector3D velocityVariance,
    float lifetime, Vector4 color, float limit_radius) :
    position(position), lifetime(lifetime), color(color),
    limit_type(BoundsType::Sphere), limit_radius(limit_radius), shape(CreateShape(physx::PxSphereGeometry(0.15f))),

    normal_dist{ // una dist normal para cada componente (con desviaciones)
        normal_distribution<float>(velocityMean.getX(), sqrt(velocityVariance.getX())),
        normal_distribution<float>(velocityMean.getY(), sqrt(velocityVariance.getY())),
        normal_distribution<float>(velocityMean.getZ(), sqrt(velocityVariance.getZ())) } {
}

// Ctra para bounding box (Vector3D box)
ParticleSystem::ParticleSystem(Vector3D position, Vector3D velocityMean, Vector3D velocityVariance,
    float lifetime, Vector4 color, Vector3D limit_box) :
    position(position), lifetime(lifetime), color(color),
    limit_type(BoundsType::Box), limit_radius(0.f), shape(CreateShape(physx::PxSphereGeometry(0.15f))),
    limit_box(limit_box),

    normal_dist{
        normal_distribution<float>(velocityMean.getX(), sqrt(velocityVariance.getX())),
        normal_distribution<float>(velocityMean.getY(), sqrt(velocityVariance.getY())),
        normal_distribution<float>(velocityMean.getZ(), sqrt(velocityVariance.getZ())) } {
}

ParticleSystem::~ParticleSystem() {
    shape->release();
}

void ParticleSystem::Particle::integrate(float dt) {
    // Semi Euler
    velocity.setY(velocity.getY() - 10.f * dt); // TODO: pasar ese -10 a atributo propagado desde Scene
    position += velocity * dt;
}

void ParticleSystem::update(float dt) {
    // recorremos el array hasta la ultima particula viva
    for (int i = actives; i > 0; --i) {
        Particle& p = particles[i - 1]; // pillamos la dir a mem de la particula viva segun i

        p.integrate(dt); // TODO: hacer posible integrar con otras opciones (friend class Particle?)
        p.life -= dt;

        // si es de tipo esfera
        if (limit_type == BoundsType::Sphere) {
            Vector3D offset = p.position - position;
            // si se pasa del limite (producto escalar con el radio al cuadrado)
            if (offset.dot(offset) > limit_radius * limit_radius) p.life = 0.f;
        }

        // si es de tipo box (y se pasa del límite, se le pasa el centro que es la relativa p.pos - pos)
        else if (!limit_box.contains(p.position - position)) p.life = 0.f;

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

        p.position = position;
        p.life = lifetime;
        p.velocity = Vector3D(normal_dist[0](generator), normal_dist[1](generator), normal_dist[2](generator));
        ++actives;
    }
}

void ParticleSystem::render() const {
    for (int i = 0; i < actives; ++i)
        renderShape(*shape, physx::PxTransform(particles[i].position), color);
}
