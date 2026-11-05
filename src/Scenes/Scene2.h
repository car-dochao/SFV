#pragma once

#include "Scene.h"
#include "ParticleSystems.h"

#include <vector>

class Scene2 : public Scene {

private:
    std::vector<ParticleSystem*> particle_systems;
    Vector3D gravity; // gravedad de la escena (propagada a los sistemas de particulas)

public:
    explicit Scene2(std::string name);
    ~Scene2() override;

    void init() override;
    void update(double dt) override;
    void render() const override;
};
