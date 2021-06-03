#ifndef AYED_TP2_COLA_HPP
#define AYED_TP2_COLA_HPP

#include "Nodo.hpp"
#include "Pila.hpp"

template <class T> class Cola {
  private:
    // variables de instancia
    Nodo<T>* inicio = nullptr;
    Nodo<T>* fin = nullptr;
    int tamano = 0;

  public:
    // funciones
    Cola() {};
    Cola(T dato) {encolar(dato);};
    Nodo<T>* getInicio() {return inicio;};
    Nodo<T>* getFin() {return fin;};
    int getTamano() {return tamano;};
    void encolar(T dato);
    T desencolar();
    void priorizar(T dato);
    bool vacia() {return inicio ? false : true;};
    void vaciar() {while(desencolar());};
    bool contiene(T dato);
    Pila<T>* toPila();
};



// definiciones de las funciones no-inline de la clase
template<typename T>
void Cola<T>::encolar(T dato) {
  if(!vacia()) {
    // si no esta vacia
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    fin->next = nuevoNodo;
    fin = nuevoNodo;
  } else {
    // si esta vacia
    fin = inicio = new Nodo<T>(dato);
  }
  tamano++;
}


template<typename T>
T Cola<T>::desencolar() {
  // el primer de la fila debe salir
  if(!vacia()) {
    // copy initialization
    T datoADevolver(inicio->dato);
    Nodo<T>* nodoABorrar = inicio;
    inicio = inicio->next;
    if(!inicio) {
      fin = nullptr;
    }
    delete nodoABorrar;
    tamano--;
    return datoADevolver;
  } else {
    return nullptr;
  }
}


// El *fin* de la cola sera el tope de la pila. No modifica this.
template<class T>
Pila<T>* Cola<T>::toPila() {
  Pila<T>* pila = new Pila<T>();
  Nodo<T>* nodoIterado = inicio;
  while(nodoIterado) {
    // trabajo con la iteracion actual
    T datoAApilar(nodoIterado->dato);
    pila->apilar(datoAApilar);
    // itero el siguiente
    nodoIterado = nodoIterado->next;
  }
  return pila;
}


template<class T>
bool Cola<T>::contiene(T dato) {
  Nodo<T>* nodoIterado = inicio;
  while(nodoIterado) {
    if(nodoIterado->dato == dato) {
      return true;
    }
    nodoIterado = nodoIterado->next;
  }
  return false;
}


// Viola el principio de una cola e ingresa un nuevo dato como prioridad, primero en la cola.
template<class T>
void Cola<T>::priorizar(T dato) {
  if(!vacia()) {
    // si no esta vacia
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    nuevoNodo->next = inicio;
    inicio = nuevoNodo;
  } else {
    // si esta vacia
    fin = inicio = new Nodo<T>(dato);
  }
  tamano++;
}

#endif
