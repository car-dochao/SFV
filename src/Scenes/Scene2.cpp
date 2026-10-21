#include "Scene2.h"

Scene2::Scene2(std::string name) : Scene(name),
    // fuente
    fountain(Vector3D(-25.f, 0.f, 25.f), // posición inicial
        Vector3D(0.f, 22.f, 0.f), Vector3D(2.f, 4.f, 2.f), // velocidad media y varianza
        5.f, Vector4(0.75f, 0.45f, 0.9f, 1.f), 80.f), // vida, color y radio límite
    // manguera
    pipe(Vector3D(0.f, 0.f, 0.f), // posición inicial
        Vector3D(9.f, 10.f, 0.f), Vector3D(1.f, 1.f, 1.f), // velocidad media y varianza
        4.f, Vector4(1.f, 1.f, 1.f, 1.f), Vector3D(60.f, 30.f, 20.f)), // vida, color y tamaño del limite
    // chispas
    sparks(Vector3D(25.f, 0.f, 20.f), // posición inicial
        Vector3D(0.f, 12.f, 0.f), Vector3D(20.f, 9.f, 20.f), // velocidad media y varianza
        3.f, Vector4(1.f, 1.f, 0.6f, 1.f), 10.f) { // vida, color y radio limite
}

void Scene2::init() {
}

void Scene2::update(double dt) {
    fountain.update(dt);
    pipe.update(dt);
    sparks.update(dt);
}

void Scene2::render() const {
    fountain.render();
    pipe.render();
    sparks.render();
}
