# TF17 — Torneo de dados

**Asignatura:** INF-5110 Laboratorio de Introducción a la Programación  
**Institución:** Universidad Autónoma de Santo Domingo (UASD)  
**Autor(es):** completar con los nombres de los integrantes.

## Descripción

Aplicación de consola en C++ para registrar participantes, configurar rondas, lanzar dos dados de seis caras por turno, acumular puntos y determinar el ganador o los ganadores compartidos.

## Reglas del torneo

- Se registran de 2 a 8 jugadores.
- Cada jugador tiene un código único y un nombre no vacío.
- Se elige entre 1 y 20 rondas antes de iniciar.
- El orden de turno es el orden de registro.
- Cada jugador lanza dos dados de seis caras en cada ronda.
- La puntuación del turno es la suma de ambos dados (2 a 12).
- Cada turno se suma una sola vez.
- Gana quien tenga el mayor acumulado; si hay empate en el máximo, todos los empatados ganan.
- No se puede modificar la configuración durante el torneo.
- El estado se conserva solamente en memoria. Al salir se pierde; no se exige persistencia en archivos.

## Estructuras y módulos

- `src/Modelos.h`: estructuras `Jugador`, `Turno`, `Ronda`, estado y datos del torneo.
- `src/Azar.h` y `src/Azar.cpp`: inicialización del generador y lanzamiento aleatorio.
- `src/Torneo.h` y `src/Torneo.cpp`: validaciones, registro, control de rondas, puntuación, marcador, ganadores y reinicio.
- `src/main.cpp`: menú e interacción con el usuario.
- `docs/PruebasManuales.md`: diez escenarios de prueba propuestos para documentar.

La colección principal de participantes es `vector<Jugador>`. El historial de rondas usa `vector<Ronda>` y cada ronda conserva los turnos aceptados.

## Requisitos

- Compilador de C++ compatible con C++17 (por ejemplo, g++).
- Git (para el historial de desarrollo).

## Compilación

Desde la carpeta raíz del proyecto:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp src/Torneo.cpp src/Azar.cpp -o torneo_dados
```

En Windows con MinGW:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic src/main.cpp src/Torneo.cpp src/Azar.cpp -o torneo_dados.exe
```

## Ejecución

Linux/macOS:

```bash
./torneo_dados
```

Windows:

```bash
torneo_dados.exe
```

Sigue el menú: registra jugadores, configura rondas, inicia el torneo y selecciona «Lanzar dados del turno actual». Puedes consultar el marcador sin consumir turnos. Al completar todos los turnos aparece el resultado final.

## Validaciones implementadas

1. Cantidad de jugadores entre 2 y 8.
2. Código y nombre no vacíos.
3. Código único.
4. Cantidad de rondas entre 1 y 20.
5. Inicio solo con configuración completa.
6. Lanzamientos solo durante un torneo en curso.
7. Cada dado debe estar entre 1 y 6.
8. Bloqueo de cambios de configuración después de iniciar.
9. Lectura de menú como entero completo, sin aceptar texto sobrante.
10. Rechazo de lanzamientos posteriores a la finalización.

## Procesamiento

- Suma de los dos dados y acumulación de puntos.
- Conteo de turnos aceptados.
- Control de avance de jugador y ronda.
- Búsqueda de la puntuación máxima y recopilación de todos los empatados.

## Pruebas

Consulta `docs/PruebasManuales.md`. Incluye diez escenarios, entre ellos entradas inválidas, límites, empates, reinicio y juego aleatorio. Los resultados observados deben completarse después de ejecutar las pruebas; no se deben presentar resultados esperados como si fueran observados.

Para probar la lógica con dados conocidos, `aceptarLanzamiento()` recibe los valores de los dados como parámetros y no depende del generador aleatorio. Se puede invocar desde un programa de prueba temporal o desde el depurador. El modo normal siempre genera los dados automáticamente.

## Git: plan de commits significativos

La guía solicita entre 5 y 8 commits realizados durante el desarrollo. Realiza estos hitos en orden, guardando los cambios reales de cada etapa:

1. `git add .` y `git commit -m "Preparar estructura inicial y documentación"`
2. `git add .` y `git commit -m "Agregar modelos y registro de jugadores"`
3. `git add .` y `git commit -m "Implementar generador aleatorio de dados"`
4. `git add .` y `git commit -m "Implementar turnos rondas y puntuaciones"`
5. `git add .` y `git commit -m "Agregar ganadores empates y reinicio"`
6. `git add .` y `git commit -m "Integrar menú y validaciones"`
7. `git add .` y `git commit -m "Documentar pruebas y completar README"`

**Importante:** estos mensajes son una planificación, no commits ya realizados. Haz cada commit al completar el hito correspondiente; no fabriques un historial retrospectivo.

## Limitaciones conocidas

- No guarda partidas en archivos, porque la ficha TF17 no exige persistencia.
- El juego normal usa dados aleatorios; los pares controlados se suministran únicamente mediante pruebas separadas.
- El registro de resultados observados y la evidencia de ejecución deben completarse en el equipo donde se compile y pruebe.
