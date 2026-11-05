#include "ForceGenerator.h"

#include <cmath>

// gravity
GravityGenerator::GravityGenerator(Vector3D gravity, Vector3D center, Vector3D bounds) :
    ForceGenerator(center, bounds), gravity(gravity) {
}

Vector3D GravityGenerator::calculateForce(const Particle& particle) const {
    if (active && bounds.contains(particle.getPosition() - center))
        return gravity * particle.getMass();

    return Vector3D(); // devolvemos vector de ceros en caso de no estar en el volumen (o no estar activo)
}

// wind
WindGenerator::WindGenerator(Vector3D center, float radius, Vector3D velocity, float k1) :
    ForceGenerator(center, Vector3D(2.f * radius, 2.f * radius, 2.f * radius)),
    radius(radius), velocity(velocity), k1(k1) {
}

Vector3D WindGenerator::calculateForce(const Particle& particle) const {
    Vector3D offset = particle.getPosition() - center;
    if (active && bounds.contains(offset) && offset.magnitude() < radius)
        return (getWindVelocity(particle.getPosition()) - particle.getVelocity()) * k1;

    return Vector3D(); // devolvemos vector de ceros en caso de no estar en el volumen (o no estar activo)
}

Vector3D WindGenerator::getWindVelocity(const Vector3D&) const {
    return velocity;
}

// vortex
VortexGenerator::VortexGenerator(Vector3D center, float radius, float strength, float k1) :
    WindGenerator(center, radius, Vector3D(), k1), strength(strength) {
}

Vector3D VortexGenerator::getWindVelocity(const Vector3D& position) const {
    Vector3D offset = position - center;
    return Vector3D(-offset.getZ(), 50.f - offset.getY(), offset.getX()) * strength;
}

// explosion
ExplosionGenerator::ExplosionGenerator(Vector3D center, float radius, float strength, float tau) :
    ForceGenerator(center, Vector3D(2.f * radius, 2.f * radius, 2.f * radius)),
    radius(radius), strength(strength), tau(tau) {
    active = false; // esperamos a que se active con su tecla
}

Vector3D ExplosionGenerator::calculateForce(const Particle& particle) const {
    Vector3D offset = particle.getPosition() - center;
    float distance = offset.magnitude();

    if (active && bounds.contains(offset) && distance > 0.f && distance < radius)
        return offset * (strength / (distance * distance) * std::exp(-elapsed / tau));

    return Vector3D(); // devolvemos vector de ceros en caso de no estar en el volumen (o no estar activo)
}

void ExplosionGenerator::trigger() {
    elapsed = 0.f; // 
    ForceGenerator::trigger();
}

void ExplosionGenerator::update(float dt) {
    if (active) {
        elapsed += dt;
        if (elapsed >= 4.f * tau) active = false;
    }
}
