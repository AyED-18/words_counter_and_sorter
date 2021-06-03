#ifndef AYED_TP2_NODODEHEAPABSTRACTO_HPP
#define AYED_TP2_NODODEHEAPABSTRACTO_HPP

// Version minimalista y padre de un #NodoDeHeap.
template <typename T> class NodoDeHeapAbstracto {
  public:
    // variables
    T dato;
    int repeticiones; // veces que el dato de este nodo se repite dentro de la estructura que conforma

    // funciones
    NodoDeHeapAbstracto(T dato, int repeticiones = 1) : dato(dato), repeticiones(repeticiones) {};
};

#endif
