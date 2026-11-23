#include "Azar.h"

namespace {
    std::mt19937& generador() {
        static std::mt19937 motor(std::random_device{}());
        return motor;
    }
}

void inicializarAzar() {
    
    (void)generador();
}

std::pair<int, int> lanzarDados() {
    std::uniform_int_distribution<int> distribucion(1, 6);
    return {distribucion(generador()), distribucion(generador())};
}
