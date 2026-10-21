#pragma once

#include "Vector3D.h"
#include "core.hpp"

#include <array>
#include <random>

using namespace std;

class ParticleSystem {

    static constexpr size_t MAX_PARTICLES = 1000;

public:

    struct Particle {
        Vector3D position;
        Vector3D velocity;
        float life = 0.f;

        void integrate(float dt);
    };

    // si es de tipo sphere (con un radius)
    ParticleSystem(Vector3D position, Vector3D velocityMean, Vector3D velocityVariance,
        float lifetime, Vector4 color, float limit_radius);

    // si es de tipo box (con un Vector3D de tamaño)
    ParticleSystem(Vector3D position, Vector3D velocityMean, Vector3D velocityVariance,
        float lifetime, Vector4 color, Vector3D limit_box);

    ~ParticleSystem();

    ParticleSystem(const ParticleSystem&) = delete;
    ParticleSystem& operator=(const ParticleSystem&) = delete;

    void update(float dt);
    void render() const;

private:

    void emmitParticle();

    physx::PxShape* shape = nullptr;
    Vector3D position;
    Vector4 color;
    float lifetime;

    enum class BoundsType { Sphere, Box } limit_type; // TODO: dejar solo de tipo box?
    float limit_radius; // el radio si el tipo de bounding es sphere
    Vector3D limit_box; // el tamaño de la caja si el tipo de bounding es de box

    array<Particle, MAX_PARTICLES> particles; // pool de particulas
    size_t actives = 0;
    array<normal_distribution<float>, 3> normal_dist; // array de tres distr normales ()

    mt19937 generator{ random_device{}() };
};
