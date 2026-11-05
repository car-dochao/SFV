#pragma once

#include "Particle.h"

// clase base
class ForceGenerator {

public:
    virtual ~ForceGenerator() = default;
    virtual Vector3D calculateForce(const Particle& particle) const = 0;
    virtual void update(float) {}
    inline virtual void trigger() { active = !active; } // togglea la actividad del generador

protected:
    ForceGenerator(Vector3D center, Vector3D bounds) : center(center), bounds(bounds) {}

    Vector3D center;
    Vector3D bounds; // limites del volumen en que se aplican fuerzas
    bool active = true;
};

// gravedad
class GravityGenerator : public ForceGenerator {

public:
    explicit GravityGenerator(Vector3D gravity, Vector3D center = Vector3D(),
        Vector3D bounds = Vector3D(200.f, 200.f, 200.f));
    Vector3D calculateForce(const Particle& particle) const override;

private:
    Vector3D gravity;
};

// viento
class WindGenerator : public ForceGenerator {

public:
    WindGenerator(Vector3D center, float radius, Vector3D velocity = Vector3D(15.f, 0.f, 0.f), float k1 = 2.f);
    Vector3D calculateForce(const Particle& particle) const override;

protected:
    virtual Vector3D getWindVelocity(const Vector3D& position) const;

private:
    float radius;
    Vector3D velocity;
    float k1;
};

// torbellinos (o vortices o como se le quiera llamar)
class VortexGenerator : public WindGenerator {

public:
    VortexGenerator(Vector3D center, float radius, float strength = 0.35f, float k1 = 2.f);

protected:
    Vector3D getWindVelocity(const Vector3D& position) const override;

private:
    float strength;
};

// explosión
class ExplosionGenerator : public ForceGenerator {

public:
    ExplosionGenerator(Vector3D center, float radius, float strength = 400.f, float tau = 0.6f);

    Vector3D calculateForce(const Particle& particle) const override;

    void trigger() override;
    void update(float dt) override;

private:
    float radius;
    float strength;
    float tau; // la cte de tiempo (a los 4 * tau dejamos de aplicar fuerza!)
    float elapsed = 0.f;
};
