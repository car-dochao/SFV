#include "Scene2.h"

Scene2::Scene2(std::string name) : Scene(name) {
}

Scene2::~Scene2() {
    for (ParticleSystem* p : particle_systems)
        delete p;
}

void Scene2::init() {
    // niebla (es un "prefab"):
    // (0, 20, 0) -> centro del emit
    // 30.f -> dispersión de la posición (0.f - 30.f)
    // 2.f -> densidad (30 / 2 = 15)
    // (1, 1, 1, 0.5) -> color
    // ... las demás estan predefinidas en la clase (consultar ParticleSystems->Fog)
    ParticleSystem* fog = new Fog(Vector3D(0, 20, 0), 30.f, 2.f, Vector4(1.0f, 1.0f, 1.0f, 0.5f)); // TODO: el alpha solo los hace wireframe, no cambia realmente la opacidad
    particle_systems.push_back(fog);

    // chorro de agua (sistema de particulas al uso, no es un "prefab")
    // (20, 0, 0) -> centro del emit
    // 0.2f -> desviación de posicion (aplica a cada eje)
    // (0, 25, 0) -> velocidad media (hacia +Y)
    // 1.5f -> desviación de velocidad (aplica a cada eje)
    // 3.f -> vida de cada particula (en sec, TODO: convendría pasar a ms supongo?)
    // (0.2, 0.4, 1, 1) -> color
    // (0, -10, 0) -> gravedad
    ParticleSystem* jet = new ParticleSystem(Vector3D(20, 0, 0), 0.2f, Vector3D(0, 25, 0),
        1.5f, 3.f, Vector4(0.2f, 0.4f, 1.f, 0.5f), Vector3(0.f, -10.f, 0.f));
    particle_systems.push_back(jet);
}

void Scene2::update(double dt) {
    for (ParticleSystem* p : particle_systems)
        p->update(float(dt));
}

void Scene2::render() const {
    for (ParticleSystem* p : particle_systems)
        p->render();
}
