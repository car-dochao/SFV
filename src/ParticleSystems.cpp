#include "ParticleSystems.h"
#include "ForceGenerator.h"
#include "RenderUtils.hpp"
#include "Render/Render.h"

ParticleSystem::ParticleSystem(Vector3D position, float pos_deviation, Vector3D velocity, float vel_deviation,
    float lifetime, Vector4 color, Vector3D gravity, float mass, Vector3D bounds) : shape(CreateShape(physx::PxSphereGeometry(0.15f))),
    position(position), bounds(bounds), velocity(velocity), color(color),
    lifetime(lifetime), mass(mass), gravity(gravity), position_dist(0.f, pos_deviation), velocity_dist(0.f, vel_deviation) {
    // si es lifetime INFINITE_LIFE se generan todas las partciculas de una (se asume que mueren por distancia y nunca mas reviven)
    if (lifetime == INFINITE_LIFE) {
        for (size_t i = 0; i < MAX_PARTICLES; ++i)
            emit();
    } // TODO: esto la verdad podría hacerse mejor?
}

ParticleSystem::~ParticleSystem() {
    shape->release();
}

void ParticleSystem::update(float dt) {
    // recorremos el array hasta la ultima particula viva
    for (size_t i = actives; i > 0; --i) {
        Particle& p = particles[i - 1]; // pillamos la dir a mem de la particula viva segun i

        // si tuviese algun ForceGenerator "vinculado", 
        // la particula lo consultaría al actualizarse para sumar la fuerza correspondiente
        p.addForce(gravity * p.getMass());
        p.update(dt, force_generators);

        // si la particula "viva" esta muerta o sale de la caja la cambiamos por la ultima viva
        if (p.getLife() <= 0.f || !bounds.contains(p.getPosition() - position)) {
            --actives;
            p = particles[actives];
        }
    }

    // emitimos una nueva particula (usando la primera de las muertas)
    // vida infinita indica que las particlas instanciadas inicialmente 
    // no mueren (a no ser que salgan de bounds) y tampoco se vuelven a emitir nuevas!
    if (lifetime != INFINITE_LIFE) emit();
}

void ParticleSystem::addForceGenerator(const ForceGenerator& force_generator) {
    force_generators.push_back(&force_generator);
}

// emite una particula usando la primera marcada como muerta, si queda hueco
void ParticleSystem::emit() {
    if (actives < MAX_PARTICLES) {
        Particle& p = particles[actives];

        // media + "ruido" de la distribucion en cada eje
        p = Particle(position + Vector3D(position_dist(generator), position_dist(generator), position_dist(generator)),
            velocity + Vector3D(velocity_dist(generator), velocity_dist(generator), velocity_dist(generator)),
            mass, lifetime, color);
        ++actives;
    }
}

void ParticleSystem::render() const {
    for (size_t i = 0; i < actives; ++i)
        renderShape(*shape, physx::PxTransform(particles[i].getPosition()), particles[i].getColor());
}
