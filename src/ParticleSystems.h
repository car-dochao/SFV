#pragma once

#include "Particle.h"
#include "core.hpp"

#include <array>
#include <limits>
#include <random>
#include <vector>

class ForceGenerator;

using namespace std;

class ParticleSystem {

static constexpr size_t MAX_PARTICLES = 1000;

public:

static constexpr float INFINITE_LIFE = numeric_limits<float>::infinity(); // para marcar vida infinita en el float!

    // las medias (position, velocity) son el valor central y los spreads la desviacion tipica del ruido
    ParticleSystem(Vector3D position, float pos_deviation, Vector3D velocity, float vel_deviation,
        float lifetime, Vector4 color, Vector3D gravity, float mass = 1.f,
        Vector3D bounds = Vector3D(200.f, 200.f, 200.f));

    virtual ~ParticleSystem();

    ParticleSystem(const ParticleSystem&) = delete;
    ParticleSystem& operator=(const ParticleSystem&) = delete;

    void update(float dt);
    void render() const;

    void addForceGenerator(const ForceGenerator& force_generator);

private:
    void emit();

    physx::PxShape* shape = nullptr;
    Vector3D position; // centro del emisor
    Vector3D bounds; // dimensiones de la caja de vida, centrada en el emisor
    Vector3D velocity; // velocidad media de emision
    Vector4 color;
    float lifetime; // vida de la particula
    float mass; // masa asignada a las particulas al emitirse
    Vector3D gravity; // gravedad propagada desde la escena

    vector<const ForceGenerator*> force_generators; // punteros a los generators de fuerzas

    array<Particle, MAX_PARTICLES> particles; // pool de particulas
    size_t actives = 0; // indice de ultima "viva"

    mt19937 generator{ random_device{}() };

    // distribuciones normales (ruido sobre la posicion y velocidad medias)
    normal_distribution<float> position_dist;
    normal_distribution<float> velocity_dist;
};


// dejo las clases de tipos predefinidos de sistemas de particulas por no andar haciendo .hs adicionales TODO: cambiar en un futuro?
class Fog : public ParticleSystem {

public:
    Fog(Vector3D position, float size, float density, Vector4 color, float mass = 1.f,
        Vector3D bounds = Vector3D(200.f, 200.f, 200.f), float lifetime = 60.f) :
    // por defecto: velocidad media 0, desviacion de velocidad 0.3, vida de 60 s y gravedad 0
        ParticleSystem(position, size / density, Vector3D(), 0.3f, lifetime, color, Vector3D(), mass, bounds) {
    };
};
