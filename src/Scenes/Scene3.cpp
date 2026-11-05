#include "Scene3.h"

Scene3::Scene3(std::string name) : Scene(name),
    gravity(Vector3D(0.f, -25.f, 0.f), Vector3D(-45.f, -30.f, 0.f), Vector3D(200.f, 100.f, 200.f)),
    negative_gravity(Vector3D(0.f, 25.f, 0.f), Vector3D(-45.f, 70.f, 0.f), Vector3D(200.f, 100.f, 200.f)),
    wind(Vector3D(-15.f, 20.f, 0.f), 12.f),
    twister(Vector3D(15.f, -5.f, 0.f), 60.f, 0.8f, 20.f),
    explosion(Vector3D(45.f, 20.f, 0.f), 12.f, 2000.f) {
}

Scene3::~Scene3() {
    for (ParticleSystem* s : particle_systems)
        delete s;
}

void Scene3::init() {
    // particulas de "niebla" (amarilla, afectada por distintas gravedades)
    ParticleSystem* yellow_fog = new Fog(Vector3D(-45.f, 20.f, 0.f), 3.f, 2.f, Vector4(1.f, 1.f, 0.f, 1.f), 3.f);
    yellow_fog->addForceGenerator(gravity);
    yellow_fog->addForceGenerator(negative_gravity);
    particle_systems.push_back(yellow_fog);

    // particulas de viento (azul)
    ParticleSystem* blue_particles = new ParticleSystem(
        Vector3D(-25.f, 20.f, 0.f), 0.1f, Vector3D(3.f, 0.f, 0.f), 0.1f,
        2.5f, Vector4(0.f, 0.f, 1.f, 1.f), Vector3D(), 5.f);
    blue_particles->addForceGenerator(wind);
    particle_systems.push_back(blue_particles);

    // particulas de vórtice (verde)
    ParticleSystem* green_particles = new ParticleSystem(
        Vector3D(15.f, 20.f, 0.f), 2.5f, Vector3D(), 0.1f, // 
        10.f, Vector4(0.f, 1.f, 0.f, 1.f), Vector3D(), 2.f); //
    green_particles->addForceGenerator(twister);
    particle_systems.push_back(green_particles);

    // particulas de explosión (rojas)
    ParticleSystem* red_particles = new ParticleSystem(
        Vector3D(45.f, 20.f, 0.f), 3.5f, Vector3D(), 0.001f, ParticleSystem::INFINITE_LIFE, // 
        Vector4(1.f, 0.f, 0.f, 1.f), Vector3D(), 4.f); //
    red_particles->addForceGenerator(explosion);
    particle_systems.push_back(red_particles);
}

void Scene3::update(double dt) {
    for (ParticleSystem* s : particle_systems)
        s->update(float(dt));

    for (ForceGenerator* g : force_generators)
        g->update(float(dt));
}

void Scene3::render() const {
    for (const ParticleSystem* s : particle_systems)
        s->render();
}

void Scene3::keyPress(unsigned char key, const physx::PxTransform&) {
    switch (key) {
    case 'g': gravity.trigger(); break; // togglea la gravedad normal
    case 'G': negative_gravity.trigger(); break; // togglea la gravedad invertida (shift + G)
    case 'v': wind.trigger(); break;  // togglea el viento
    case 't': twister.trigger(); break; // togglea el tornado
    case 'e': explosion.trigger(); break; // togglea la explosion
    }
}
