#pragma once

#include "Scene.h"
#include "ForceGenerator.h"
#include "ParticleSystems.h"

#include <array>
#include <vector>

class Scene3 : public Scene {

public:
    explicit Scene3(std::string name);
    ~Scene3() override;

    void init() override;
    void update(double dt) override;
    void render() const override;
    void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override;

private:
    GravityGenerator gravity;
    GravityGenerator negative_gravity;
    WindGenerator wind;
    VortexGenerator twister;
    ExplosionGenerator explosion;

    // array de punteros a generadores (tipo sistemas)
    std::array<ForceGenerator*, 5> force_generators{ &gravity, &negative_gravity, &wind, &twister, &explosion };

    // vector de sistemas de particulas
    std::vector<ParticleSystem*> particle_systems;
};
