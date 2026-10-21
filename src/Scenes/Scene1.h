#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"


class Scene1 : public Scene {

private:
    std::vector<RenderItem*> m_renderItems;
    std::vector<Particle*> m_particles;

    float real_mass;
    float real_velocity;
    float sim_velocity;

    Vector3D gravity;

    void shoot(); // dispara un proyectil desde la cámara

public:
    explicit Scene1(std::string name);
    ~Scene1() override;

    void init() override;
    void update(double dt) override;
    void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;
};
