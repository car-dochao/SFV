#include "Scene0.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"

Scene0::Scene0(std::string name) : Scene(name) {

}

void Scene0::init() {
    // Esfera en (0, 0, 0)
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
    m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));

    // Se registra el RenderItem exactamente como en la plantilla original
    m_renderItems.push_back(new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 0.0f, 1.0f)));
}

void Scene0::update(double dt) {
}

Scene0::~Scene0() {
    for (RenderItem* item : m_renderItems)
        if (item) {
            item->release(); // Deregistra y destruye el item
        }
}