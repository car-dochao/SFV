#include "Scene1.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "Projectile.h"

Scene1::Scene1(std::string name) :
    Scene(name),
    // bala de cañón (500m/s y 6kg)
    real_mass(6.f), real_velocity(500.f), sim_velocity(50.f), gravity(0, -9.8f, 0) {
}

void Scene1::init() {
    // Añadimos una partícula
    //m_particles.push_back(new Particle({0, 0, 0}, {2, 0, 0})); // velocidad 2m/s?

    // Esfera que sirve como diana
    // physx::PxTransform m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));
    // m_renderItems.push_back(new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &m_transform, Vector4(1.0f, 0.1f, 0.1f, 1.0f)));
}

void Scene1::update(double dt) {
    for (Particle* particle : m_particles)
        if (particle) particle->update(dt);
}

Scene1::~Scene1() {
    for (RenderItem* item : m_renderItems)
        if (item) {
            item->release(); // Deregistra y destruye el item
        }

    for (Particle* particle : m_particles)
        if (particle) delete particle;

}

void Scene1::keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {
    // Teclas globales de navegación entre prácticas
    switch (key) {
    case 'e': // disparar proyectil
        shoot();
        return;
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

void Scene1::shoot() {
    Vector3D position = GetCamera()->getEye();
    Vector3D direction = GetCamera()->getDir();

    m_particles.push_back(new Projectile(position, direction, real_mass,
        gravity, sim_velocity, real_velocity));
}
