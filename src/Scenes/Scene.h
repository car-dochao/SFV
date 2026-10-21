#pragma once

#include <string>
#include "PxPhysicsAPI.h"

// Clase base para las distintas escenas de la aplicación.
// Provee la interfaz mínima que debe implementar cualquier escena:
// inicialización, limpieza, actualización por frame y manejo de teclado.
class Scene {

public:
    // Construye la escena con un nombre identificador.
    explicit Scene(std::string name) : m_name(std::move(name)) {}
    virtual ~Scene() = default;

    // Inicializa recursos de la escena (físicos, gráficos, datos, ...).
    virtual void init() = 0;

    // Actualiza la lógica de la escena.
    // dt: tiempo en segundos transcurrido desde la última actualización.
    virtual void update(double dt) = 0;

    // para propagar a sistemas como ParticleSystem TODO: plantear otras formas de hacerlo evitando render en scenes virtual
    // (el orden de update-> render importa, en caso de hacer un render en el propio update las particulas no se ven)
    virtual void render() const {}

    // Manejo de pulsación de tecla.
    // Se recibe la tecla pulsada y la transformada de la cámara para
    // permitir respuestas dependientes de la orientación/posición de la cámara.
    // Método opcional que puede ser sobrescrito por escenas que lo necesiten.
    virtual void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) {}

    // Devuelve el nombre identificador de la escena.
    [[nodiscard]] const std::string& getName() const { return m_name; }

protected:
    // Nombre de la escena (útil para identificarla en menos o logs).
    std::string m_name;
};