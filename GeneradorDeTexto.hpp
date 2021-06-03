#ifndef TP2_GENERADOR_DE_TEXTO_HPP
#define TP2_GENERADOR_DE_TEXTO_HPP

#include "Pila.hpp"
#include "NodoDeHeapAbstracto.hpp"
#include <string>

// Una instancia de esta clase, tiene objetivo final producir un archivo de palabras ordenadas.
class GeneradorDeTexto{
  public:
    // funciones
    std::string generarArchivoFinal(Pila<NodoDeHeapAbstracto<std::string>*>* ordenada,
                               std::string nombreArchivo, int aridad);
};

#endif