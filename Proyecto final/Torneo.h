#ifndef TORNEO_H
#define TORNEO_H

#include "Modelos.h"
#include <string>
#include <vector>

bool codigoExiste(const Torneo& torneo, const std::string& codigo);
bool registrarJugador(Torneo& torneo, const std::string& codigo,
                      const std::string& nombre, std::string& mensaje);
bool configurarRondas(Torneo& torneo, int cantidad, std::string& mensaje);
bool iniciarTorneo(Torneo& torneo, std::string& mensaje);
bool aceptarLanzamiento(Torneo& torneo, int dado1, int dado2, std::string& mensaje);
int obtenerMaximo(const Torneo& torneo);
std::vector<Jugador> obtenerGanadores(const Torneo& torneo);
void mostrarMarcador(const Torneo& torneo);
void reiniciarTorneo(Torneo& torneo);

#endif
