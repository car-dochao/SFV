#include "Scene1.h"
#include "RenderUtils.hpp"
#include "Render/Render.h"
#include "Vector3D.h"
#include "Particle.h"
#include "Projectile.h"

Scene1::Scene1(std::string name) :
    Scene(name), shape(CreateShape(physx::PxSphereGeometry(1.f))),
    // bala de cañón (500m/s y 6kg)
    real_mass(6.f), real_velocity(500.f), sim_velocity(50.f), gravity(0, -9.8f, 0) {
}

void Scene1::update(double dt) {
    for (Particle* particle : m_particles)
        if (particle) particle->update(dt);
}

void Scene1::render() const {
    for (const Particle* particle : m_particles)
        renderShape(*shape, physx::PxTransform(particle->getPosition()), particle->getColor());
}

Scene1::~Scene1() {
    for (Particle* particle : m_particles)
        if (particle) delete particle;

    shape->release();
}

void Scene1::keyPress(unsigned char key, const physx::PxTransform&) {
    switch (key) {
    case 'e': // bala de cañón, configurable con mM/vV
        shoot(real_mass, real_velocity, Vector4(0.f, 0.f, 0.f, 1.f));
        break;
    case 'r': // bala (20 g y 800 m/s, no configurable como la de cañón!)
        shoot(0.02f, 800.f, Vector4(1.f, 1.f, 1.f, 1.f));
        break;
    case 'm': // elevar masa del proximo proyectil
        real_mass += 1.f;
        break;
    case 'M': // restar masa del proximo proyectil (shift + m)
        real_mass -= 1.f;
        break;
    case 'v': // sumar velocidad del proximo proyectil
        real_velocity += 20.f;
        break;
    case 'V': // restar velocidad del proximo proyectil (shift + v)
        real_velocity -= 20.f;
        break;
    default:
        return;
    }
}

void Scene1::shoot(float mass, float speed, Vector4 color) {
    Vector3D position = GetCamera()->getEye();
    Vector3D direction = GetCamera()->getDir();

    m_particles.push_back(new Projectile(position, direction, mass,
        gravity, sim_velocity, speed, color));
}
