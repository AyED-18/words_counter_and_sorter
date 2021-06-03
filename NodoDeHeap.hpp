#ifndef AYED_TP2_NODODEHEAP_HPP
#define AYED_TP2_NODODEHEAP_HPP

#include "NodoDeHeapAbstracto.hpp"
#include "Pila.hpp"

template <typename T> class Heap;

// Componente de un #Heap.
template <typename T> class NodoDeHeap : public NodoDeHeapAbstracto<T> {

  // permitir a una instancia de Heap<U>, acceder a los miembros privados de un #NodoDeHeap<T>
  template <typename U> friend class Heap;

  private:
    // variables
    NodoDeHeap<T>* padre;
    Pila<NodoDeHeap<T>*>* hijos;

    // funciones
    int cantidadDeHijos() {return hijos->getTamano();};

  public:
    // funciones
    NodoDeHeap(T dato, NodoDeHeap<T>* padre = nullptr) :
      NodoDeHeapAbstracto<T>(dato), padre(padre) {hijos = new Pila<NodoDeHeap<T>*>();};
};

#endif
