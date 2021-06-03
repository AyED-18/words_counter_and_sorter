#ifndef AYED_TP2_NODO_HPP
#define AYED_TP2_NODO_HPP

// Cada instancia de esta clase es de utilidad para una #Cola o #Pila.
template <typename T> class Nodo {
  public:
    // variables de instancia
    T dato;
    Nodo<T>* next;

    // funciones
    Nodo(T dato) : dato(dato), next(nullptr) {};
    Nodo(T dato, Nodo<T>* next) : dato(dato), next(next) {};
};

#endif
