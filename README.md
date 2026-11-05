# Simulación Física para Videojuegos (SFV)

## Controles

- **Generales:** `0`, `1`, `2`, `3` cambian de escena; `WASD` mueve la cámara; ratón pulsando para mirar; `Esc` para salir.

- **Escena 1 — proyectiles:**
  - `e`: cañón negro, inicialmente 6 kg y 500 m/s.
  - `r`: bala ligera blanca, 0,02 kg y 800 m/s.
  - `m` / `M` (shift + m): sumar / restar 1 kg al próximo cañón.
  - `v` / `V` (shift + v): sumar / restar 20 m/s al próximo cañón.

- **Escena 2 — partículas:** niebla y chorro (no hay controles en esta escena)

- **Escena 3 — fuerzas:** cada tecla activa/desactiva su generador:
  - `g` / `G` (shift + g): gravedad normal / gravedad invertida (sobre la nube amarilla)
  - `v`: viento (partículas azules)
  - `t`: torbellino (partículas verdes)
  - `e`: explosión  (partículas rojas)

## Requisitos de programación

- **A.1)** Integración Euler y Semi-Euler: [Particle.cpp](src/Particle.cpp#L32-L44) 32-44.
- **A.2)** Masa como parámetro: [Particle.h](src/Particle.h#L12-L27) 12-27. Partículas de distintas masas: [Scene3.cpp](src/Scenes/Scene3.cpp#L16-L43) 16-43.
- **A.3)** Fuerzas y aceleración según la masa: [Particle.cpp](src/Particle.cpp#L11-L30) 11-30.
- **B)** Proyectil y escalado: [Projectile.cpp](src/Projectile.cpp#L3-L20) 3-20. Dos tipos de disparo: [Scene1.cpp](src/Scenes/Scene1.cpp#L31-L37) 31-37.
- **C)** Sistema con pool de objetos `Particle`, actualización y renderizado: [ParticleSystems.h](src/ParticleSystems.h#L15-L60) 15-60; [ParticleSystems.cpp](src/ParticleSystems.cpp#L21-L64) 21-64, (la generación está integrada dentro del sistema de particulas).
- **D.1 y D.3)** No implementados como generador independiente como tal, sino dentro de ParticleSystem y con los atributos iniciales de la particula dada. La emisión se realiza en el método `emit()`: [ParticleSystems.cpp](src/ParticleSystems.cpp#L49-L59) 49-59.
- **D.2)** Distribuciones normales de posición y velocidad: [ParticleSystems.h](src/ParticleSystems.h#L55-L59) 55-59; [ParticleSystems.cpp](src/ParticleSystems.cpp#L49-L59) 49-59.
- **E.1)** La partícula consulta individualmente los generadores: [Particle.cpp](src/Particle.cpp#L16-L19) 16-19.
- **E.2)** Acumulación de varias fuerzas: [Particle.cpp](src/Particle.cpp#L16-L19) 16-19. Ejemplo con dos gravedades contrarias: [Scene3.cpp](src/Scenes/Scene3.cpp#L18-L21) 18-21 (se probó con distintas masas y particulas sueltas para cada generador de fuerzas pero no se incluyó por mantener el código legible).
- **E.3)** Registro de generadores por sistema: [ParticleSystems.h](src/ParticleSystems.h#L50-L52) 50-52; [ParticleSystems.cpp](src/ParticleSystems.cpp#L44-L46) 44-46. Generadores independientes almacenados en la escena: [Scene3.h](src/Scenes/Scene3.h#L22-L29) 22-29.
- **E.4)** Fuerza dependiente de posición (vórtice) y de tiempo (explosión): [ForceGenerator.cpp](src/ForceGenerator.cpp#L40-L72) 40-72.