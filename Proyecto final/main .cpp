#include "Modelos.h"
#include "Torneo.h"
#include "Azar.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <string>

bool leerEntero(const std::string& mensaje, int& valor) {
    while (true) {
        std::cout << mensaje;
        std::string linea;
        if (!std::getline(std::cin, linea)) return false;
        std::stringstream entrada(linea);
        char sobrante;
        if ((entrada >> valor) && !(entrada >> sobrante)) return true;
        std::cout << "Entrada inválida. Escribe un número entero sin texto adicional.\n";
    }
}

void registrarJugadores(Torneo& torneo) {
    int cantidad;
    if (!leerEntero("¿Cuántos jugadores deseas registrar (2-8)? ", cantidad)) return;
    if (cantidad < 2 || cantidad > 8) {
        std::cout << "Debes elegir entre 2 y 8 jugadores.\n";
        return;
    }
    for (int i = 0; i < cantidad; ++i) {
        std::string codigo, nombre, mensaje;
        std::cout << "\nJugador " << (i + 1) << "\nCódigo: ";
        std::getline(std::cin, codigo);
        std::cout << "Nombre: ";
        std::getline(std::cin, nombre);
        if (!registrarJugador(torneo, codigo, nombre, mensaje)) {
            std::cout << mensaje << "\nVuelve a intentar este registro.\n";
            --i;
        } else std::cout << mensaje << "\n";
    }
}

void mostrarResultado(const Torneo& torneo) {
    if (torneo.estado != Estado::Finalizado) {
        std::cout << "El torneo todavía no ha finalizado.\n";
        return;
    }
    std::cout << "\n========== RESULTADO FINAL ==========\n";
    mostrarMarcador(torneo);
    std::vector<Jugador> ganadores = obtenerGanadores(torneo);
    if (ganadores.size() == 1) {
        std::cout << "Ganador: " << ganadores[0].nombre
                  << " (" << ganadores[0].codigo << ")\n";
    } else {
        std::cout << "¡Empate! Ganadores compartidos:\n";
        for (const Jugador& jugador : ganadores)
            std::cout << "- " << jugador.nombre << " (" << jugador.codigo << ")\n";
    }
    std::cout << "=====================================\n";
}

void jugarTurno(Torneo& torneo) {
    if (torneo.estado != Estado::EnCurso) {
        std::cout << "Primero debes iniciar el torneo y debe estar en curso.\n";
        return;
    }
    const Jugador& jugador = torneo.jugadores[torneo.jugadorActual];
    std::cout << "\nRonda " << (torneo.rondaActual + 1) << " de " << torneo.totalRondas
              << " | Turno de " << jugador.nombre << " (" << jugador.codigo << ")\n";
    auto dados = lanzarDados();
    std::cout << "Dado 1: " << dados.first << " | Dado 2: " << dados.second << "\n";
    std::string mensaje;
    if (aceptarLanzamiento(torneo, dados.first, dados.second, mensaje))
        std::cout << mensaje << "\n";
    if (torneo.estado == Estado::Finalizado) mostrarResultado(torneo);
}

int main() {
    inicializarAzar();
    Torneo torneo;
    int opcion = -1;

    while (opcion != 0) {
        std::cout << "\n========== TORNEO DE DADOS ==========\n"
                  << "Estado: ";
        if (torneo.estado == Estado::Configuracion) std::cout << "Configuración\n";
        else if (torneo.estado == Estado::EnCurso) std::cout << "En curso\n";
        else std::cout << "Finalizado\n";

        std::cout << "1. Registrar jugadores\n"
                  << "2. Configurar cantidad de rondas\n"
                  << "3. Iniciar torneo\n"
                  << "4. Lanzar dados del turno actual\n"
                  << "5. Consultar marcador\n"
                  << "6. Ver resultado final\n"
                  << "7. Preparar un torneo nuevo\n"
                  << "0. Salir\n";

        if (!leerEntero("Selecciona una opción: ", opcion)) break;
        std::string mensaje;
        switch (opcion) {
            case 1:
                if (torneo.estado != Estado::Configuracion)
                    std::cout << "No puedes modificar jugadores después de iniciar.\n";
                else registrarJugadores(torneo);
                break;
            case 2: {
                int rondas;
                if (torneo.estado != Estado::Configuracion)
                    std::cout << "No puedes cambiar las rondas después de iniciar.\n";
                else if (leerEntero("Cantidad de rondas (1-20): ", rondas)) {
                    configurarRondas(torneo, rondas, mensaje);
                    std::cout << mensaje << "\n";
                }
                break;
            }
            case 3:
                iniciarTorneo(torneo, mensaje);
                std::cout << mensaje << "\n";
                break;
            case 4: jugarTurno(torneo); break;
            case 5: mostrarMarcador(torneo); break;
            case 6: mostrarResultado(torneo); break;
            case 7:
                if (torneo.estado == Estado::EnCurso) {
                    std::cout << "No se puede reiniciar mientras el torneo está en curso.\n";
                } else {
                    std::string confirmacion;
                    std::cout << "¿Preparar un torneo nuevo? Se borrarán los datos actuales (S/N): ";
                    std::getline(std::cin, confirmacion);
                    if (confirmacion == "S" || confirmacion == "s") {
                        reiniciarTorneo(torneo);
                        std::cout << "Torneo reiniciado. Registra nuevamente los jugadores.\n";
                    } else std::cout << "Reinicio cancelado.\n";
                }
                break;
            case 0: break;
            default: std::cout << "Opción no válida. Selecciona una opción del menú.\n";
        }
    }
    std::cout << "Al salir, el torneo en memoria termina. ¡Hasta luego!\n";
    return 0;
}
