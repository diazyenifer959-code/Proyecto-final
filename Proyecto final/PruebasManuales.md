# Registro de pruebas manuales — TF17 Torneo de dados

**Versión:** 1.0  
**Fecha de ejecución:** completar al ejecutar en el equipo del estudiante.  
**Compilador/estándar:** g++ / C++17 (ajustar si se utiliza otra herramienta).

> Importante: los resultados esperados se derivan de la guía. La columna «Resultado observado» queda pendiente hasta que el estudiante ejecute cada prueba en su equipo. No marcar como aprobada una prueba que no se haya ejecutado.

| ID | Objetivo y entradas | Resultado esperado | Resultado observado | Estado |
|---|---|---|---|---|
| P01 | Intentar iniciar sin jugadores; luego registrar un nombre vacío y repetir un código. | No inicia sin 2 jugadores; rechaza nombre vacío y código duplicado sin alterar registros válidos. | Pendiente de ejecución. | Pendiente |
| P02 | Intentar registrar 1 o 9 jugadores; configurar 0 y 21 rondas. | Rechaza valores fuera de los rangos 2–8 jugadores y 1–20 rondas. | Pendiente de ejecución. | Pendiente |
| P03 | Tres jugadores, tres rondas. Suministrar para la ronda 1: Ana 3 y 4; Luis 1 y 5; Rosa 5 y 5. | Marcadores: Ana 7, Luis 6, Rosa 10. Solo después de Rosa comienza la ronda 2. | Pendiente de ejecución. | Pendiente |
| P04 | Completar los pares controlados de las tres rondas de la guía. | Ana 24, Luis 23, Rosa 24; nueve turnos aceptados; Ana y Rosa comparten el primer lugar. | Pendiente de ejecución. | Pendiente |
| P05 | Al finalizar P04, consultar resultado e intentar lanzar otra vez. | Presenta a Ana y Rosa como ganadoras; no acepta otra tirada ni cambia los totales. | Pendiente de ejecución. | Pendiente |
| P06 | Consultar el marcador entre turnos e intentar registrar jugadores o cambiar rondas durante el torneo. | La consulta no altera el estado; los cambios de configuración son rechazados. | Pendiente de ejecución. | Pendiente |
| P07 | En una prueba controlada, intentar un dado 0 o 7 y luego un par válido. | Rechaza el par inválido completo; no suma puntos ni avanza el turno. El par válido posterior se acepta. | Pendiente de ejecución. | Pendiente |
| P08 | Reiniciar y jugar dos personas durante una ronda con pares 1 y 1; 6 y 6. | Totales 2 y 12; gana la segunda persona; no arrastra puntuaciones anteriores. | Pendiente de ejecución. | Pendiente |
| P09 | Ejecutar un torneo normal con dados aleatorios y registrar cada par. | Cada dado está entre 1 y 6; cada suma entre 2 y 12; el marcador coincide con las sumas observadas. | Pendiente de ejecución. | Pendiente |
| P10 | Escribir letras en el menú y probar 2 jugadores y 1 ronda. | Recupera la entrada inválida; acepta la configuración mínima y finaliza después de dos turnos. | Pendiente de ejecución. | Pendiente |

## Cómo realizar las pruebas controladas P03, P04, P07 y P08

La función `aceptarLanzamiento()` recibe los dos valores como argumentos, separada del generador aleatorio. Para probarla con pares conocidos, se puede crear temporalmente un pequeño programa de prueba que incluya `Torneo.h` y enlace `Torneo.cpp`, o usar el depurador para llamar la función con los pares indicados. No habilites la elección de dados por parte del usuario en el juego normal.

Pares de referencia de la guía:

| Ronda | Ana | Luis | Rosa |
|---|---|---|---|
| 1 | 3 y 4 = 7 | 1 y 5 = 6 | 5 y 5 = 10 |
| 2 | 2 y 6 = 8 | 6 y 6 = 12 | 1 y 3 = 4 |
| 3 | 4 y 5 = 9 | 2 y 3 = 5 | 4 y 6 = 10 |

## Correcciones y observaciones

Anota aquí los defectos encontrados, la corrección aplicada y la repetición de la prueba. No registres resultados supuestos.
