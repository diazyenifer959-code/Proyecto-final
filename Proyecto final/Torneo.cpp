#include "Torneo.h"
#include <iostream>
#include <algorithm>

bool codigoExiste(const Torneo& torneo, const std::string& codigo) {
    for (const Jugador& jugador : torneo.jugadores) {
        if (jugador.codigo == codigo) return true;
    }
    return false;
}

bool registrarJugador(Torneo& torneo, const std::string& codigo,
                      const std::string& nombre, std::string& mensaje) {
    if (torneo.estado != Estado::Configuracion) {
        mensaje = "No se pueden registrar jugadores despues de iniciar el torneo.";
        return false;
    }
    if (torneo.jugadores.size() >= 8) {
        mensaje = "Se permite un maximo de 8 jugadores.";
        return false;
    }
    if (codigo.empty() || nombre.empty()) {
        mensaje = "El codigo y el nombre no pueden estar vacíos.";
        return false;
    }
    if (codigoExiste(torneo, codigo)) {
        mensaje = "Ese codigo ya está registrado.";
        return false;
    }
    torneo.jugadores.push_back({codigo, nombre, 0});
    mensaje = "Jugador registrado correctamente.";
    return true;
}

bool configurarRondas(Torneo& torneo, int cantidad, std::string& mensaje) {
    if (torneo.estado != Estado::Configuracion) {
        mensaje = "No se pueden cambiar las rondas durante o despues del torneo.";
        return false;
    }
    if (cantidad < 1 || cantidad > 20) {
        mensaje = "La cantidad de rondas debe estar entre 1 y 20.";
        return false;
    }
    torneo.totalRondas = cantidad;
    mensaje = "Cantidad de rondas configurada.";
    return true;
}

bool iniciarTorneo(Torneo& torneo, std::string& mensaje) {
    if (torneo.estado != Estado::Configuracion) {
        mensaje = "El torneo no esta en estado de configuracion.";
        return false;
    }
    if (torneo.jugadores.size() < 2 || torneo.jugadores.size() > 8) {
        mensaje = "Debes registrar entre 2 y 8 jugadores.";
        return false;
    }
    if (torneo.totalRondas < 1 || torneo.totalRondas > 20) {
        mensaje = "Configura primero entre 1 y 20 rondas.";
        return false;
    }
    torneo.rondas.clear();
    for (int i = 1; i <= torneo.totalRondas; ++i) {
        torneo.rondas.push_back({i, {}});
    }
    torneo.rondaActual = 0;
    torneo.jugadorActual = 0;
    torneo.turnosAceptados = 0;
    for (Jugador& jugador : torneo.jugadores) jugador.puntuacion = 0;
    torneo.estado = Estado::EnCurso;
    mensaje = "¡El torneo ha comenzado!";
    return true;
}

bool aceptarLanzamiento(Torneo& torneo, int dado1, int dado2, std::string& mensaje) {
    if (torneo.estado != Estado::EnCurso) {
        mensaje = "No se aceptan lanzamientos: el torneo no esta en curso.";
        return false;
    }
    if (dado1 < 1 || dado1 > 6 || dado2 < 1 || dado2 > 6) {
        mensaje = "Lanzamiento valido: cada dado debe estar entre 1 y 6.";
        return false;
    }
    if (torneo.rondaActual >= torneo.totalRondas ||
        torneo.jugadorActual >= static_cast<int>(torneo.jugadores.size())) {
        mensaje = "El estado del turno no es valido.";
        return false;
    }

    Jugador& jugador = torneo.jugadores[torneo.jugadorActual];
    int puntos = dado1 + dado2;
    jugador.puntuacion += puntos;
    torneo.rondas[torneo.rondaActual].turnos.push_back(
        {jugador.codigo, dado1, dado2, puntos});
    ++torneo.turnosAceptados;

    ++torneo.jugadorActual;
    if (torneo.jugadorActual == static_cast<int>(torneo.jugadores.size())) {
        torneo.jugadorActual = 0;
        ++torneo.rondaActual;
        if (torneo.rondaActual == torneo.totalRondas) {
            torneo.estado = Estado::Finalizado;
        }
    }
    mensaje = "Lanzamiento aceptado: se sumaron " + std::to_string(puntos) + " puntos.";
    return true;
}

int obtenerMaximo(const Torneo& torneo) {
    if (torneo.jugadores.empty()) return 0;
    int maximo = torneo.jugadores.front().puntuacion;
    for (const Jugador& jugador : torneo.jugadores)
        if (jugador.puntuacion > maximo) maximo = jugador.puntuacion;
    return maximo;
}

std::vector<Jugador> obtenerGanadores(const Torneo& torneo) {
    std::vector<Jugador> ganadores;
    if (torneo.estado != Estado::Finalizado || torneo.jugadores.empty()) return ganadores;
    int maximo = obtenerMaximo(torneo);
    for (const Jugador& jugador : torneo.jugadores)
        if (jugador.puntuacion == maximo) ganadores.push_back(jugador);
    return ganadores;
}

void mostrarMarcador(const Torneo& torneo) {
    std::cout << "\n========== MARCADOR ==========\n";
    for (const Jugador& jugador : torneo.jugadores)
        std::cout << jugador.codigo << " | " << jugador.nombre
                  << " | " << jugador.puntuacion << " puntos\n";
    std::cout << "Turnos aceptados: " << torneo.turnosAceptados << "\n";
    if (torneo.estado == Estado::EnCurso) {
        std::cout << "Ronda actual: " << (torneo.rondaActual + 1)
                  << " de " << torneo.totalRondas << "\n";
        std::cout << "Turno de: " << torneo.jugadores[torneo.jugadorActual].nombre << "\n";
    }
    std::cout << "==============================\n";
}

void reiniciarTorneo(Torneo& torneo) {
    torneo.jugadores.clear();
    torneo.rondas.clear();
    torneo.totalRondas = 0;
    torneo.rondaActual = 0;
    torneo.jugadorActual = 0;
    torneo.turnosAceptados = 0;
    torneo.estado = Estado::Configuracion;
}
