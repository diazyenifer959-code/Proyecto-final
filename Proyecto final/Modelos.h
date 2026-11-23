#ifndef MODELOS_H
#define MODELOS_H

#include <string>
#include <vector>

struct Jugador {
    std::string codigo;
    std::string nombre;
    int puntuacion = 0;
};

struct Turno {
    std::string codigoJugador;
    int dado1 = 0;
    int dado2 = 0;
    int puntos = 0;
};

struct Ronda {
    int numero = 0;
    std::vector<Turno> turnos;
};

enum class Estado { Configuracion, EnCurso, Finalizado };

struct Torneo {
    std::vector<Jugador> jugadores;
    std::vector<Ronda> rondas;
    int totalRondas = 0;
    int rondaActual = 0;       
    int jugadorActual = 0;     
    int turnosAceptados = 0;
    Estado estado = Estado::Configuracion;
};

#endif
