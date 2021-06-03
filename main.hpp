#ifndef AYED_TP2_MAIN_HPP
#define AYED_TP2_MAIN_HPP

#include <string>
#include "InterpretadorDeTexto.hpp"
#include "Heap.hpp"

//prototipado de funciones
void ejecutarBienvenida();
int obtenerAridad();
std::string obtenerRuta();
std::string obtenerTexto(std::string ruta);
void imprimirComparaciones(Heap<std::string>* heap);

#endif
