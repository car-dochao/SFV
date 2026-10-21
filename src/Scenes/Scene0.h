#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"

class Scene0 : public Scene {

private:
    physx::PxTransform m_transform;
    std::vector<RenderItem*> m_renderItems;

public:
    explicit Scene0(std::string name);
    ~Scene0() override;

    void init() override;
    void update(double dt) override;
};