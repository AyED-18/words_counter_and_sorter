#ifndef AYED_TP2_INTERPRETADOR_DE_TEXTO_HPP
#define AYED_TP2_INTERPRETADOR_DE_TEXTO_HPP

#include <string>
#include "Heap.hpp"

// Una instancia de esta clase, tiene objetivo final leer e interpretar texto.
class InterpretadorDeTexto {
	public:
		Heap<std::string>* interpretarTexto(std::string texto, int aridad);
};

#endif