#ifndef AYED_TP2_PILA_HPP
#define AYED_TP2_PILA_HPP

#include "Nodo.hpp"

// definicion de clase
template <class T> class Pila {
  private:
    // variables de instancia
    Nodo<T>* tope = nullptr;
    int tamano = 0;

  public:
    // funciones
    Pila() {};
    Pila(T dato) : tope(new Nodo<T>(dato)), tamano(1) {};
    Nodo<T>* getTope() {return tope;};
    int getTamano() {return tamano;};
    bool vacia() {return tamano == 0;};
    void apilar(T dato);
    T desapilar();
};



// definiciones de las funciones no-inline de la clase
template<typename T>
void Pila<T>::apilar(T dato) {
  tope = new Nodo<T>(dato, tope);
  tamano++;
}


template <typename T>
T Pila<T>::desapilar() {
  if(tope) {
    // copy initialization
    T datoADevolver(tope->dato);
    Nodo<T>* nodoABorrar = tope;
    tope = tope->next;
    delete nodoABorrar;
    tamano--;
    return datoADevolver;
  } else {
    return nullptr;
  }
}

#endif
