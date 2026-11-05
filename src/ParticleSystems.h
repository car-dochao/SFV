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
    };

    // las medias (position, velocity) son el valor central y los spreads la desviacion tipica del ruido
    ParticleSystem(Vector3D position, float pos_deviation, Vector3D velocity, float vel_deviation,
        float lifetime, Vector4 color, Vector3D gravity);

    virtual ~ParticleSystem();

    ParticleSystem(const ParticleSystem&) = delete;
    ParticleSystem& operator=(const ParticleSystem&) = delete;

    void update(float dt);
    void render() const;

private:
    void emmitParticle();

    physx::PxShape* shape = nullptr;
    Vector3D position; // centro del emisor
    Vector3D velocity; // velocidad media de emision
    Vector4 color;
    float lifetime;
    Vector3D gravity; // gravedad propagada desde la escena

    array<Particle, MAX_PARTICLES> particles; // pool de particulas
    size_t actives = 0;

    mt19937 generator{ random_device{}() };

    // distribuciones normales (ruido sobre la posicion y velocidad medias)
    normal_distribution<float> position_dist;
    normal_distribution<float> velocity_dist;
};


// dejo las clases de tipos predefinidos de sistemas de particulas por no andar haciendo .hs adicionales TODO: cambiar en un futuro?
class Fog : public ParticleSystem {

public:
    
    Fog(Vector3D position, float size, float density, Vector4 color) :
    // por defecto: velocidad media 0, desviacion de velocidad 0.3, vida de 60 s y gravedad 0
        ParticleSystem(position, size / density, Vector3D(), 0.3f, 60.f, color, Vector3D()) {
    };
};
