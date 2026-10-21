#pragma once

#include "Scene.h"
#include "ParticleSystem.h"

class Scene2 : public Scene {

private:
    ParticleSystem fountain; // fuente
    ParticleSystem pipe; // manguera
    ParticleSystem sparks; // chispas

public:
    explicit Scene2(std::string name);

    void init() override;
    void update(double dt) override;
    void render() const override;
};
