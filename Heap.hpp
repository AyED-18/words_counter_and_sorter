#ifndef AYED_TP2_HEAP_HPP
#define AYED_TP2_HEAP_HPP

#include "Nodo.hpp"
#include "Cola.hpp"
#include "Pila.hpp"
#include "NodoDeHeapAbstracto.hpp"
#include "NodoDeHeap.hpp"

// Arbol-heap n-ario.
template <typename T> class Heap {

  private:
    // variables
    NodoDeHeap<T>* raiz;
    Cola<NodoDeHeap<T>*>* helperUbicNewNodos; // helper para ubicar rapidamente nuevos nodos
    Cola<NodoDeHeap<T>*>* helperUbicNewNodos2; // otro helper para ubicar rapidamente nuevos nodos

    // funciones
    NodoDeHeap<T>* existeDato(T dato, NodoDeHeap<T>* nodoReferencial);
    NodoDeHeap<T>* ingresarNuevoNodo(T dato);
    bool ordenar(NodoDeHeap<T>* nodoCausal, bool aguasArriba);

  public:
    // variables
    int aridad;
    int swapsDeOrdenarAguasArriba = 0;
    int swapsDeOrdenarAguasAbajo = 0;
    int swapsDeToPila = 0;
    int comparaciones = 0;

    // funciones
    Heap(int aridad, T datoRaiz);
    void ingresarDato(T dato);
    Pila<NodoDeHeapAbstracto<T>*>* toPila();
    int swapsTotales() {return swapsDeOrdenarAguasArriba + swapsDeOrdenarAguasAbajo + swapsDeToPila;};
};



// FUNCIONES PUBLICAS
// definiciones de las funciones no-inline de la clase
template <typename T>
Heap<T>::Heap(int aridad, T datoRaiz) {
  this->aridad = aridad;
  raiz = new NodoDeHeap<T>(datoRaiz);
  helperUbicNewNodos = new Cola<NodoDeHeap<T>*>(raiz);
  helperUbicNewNodos2 = new Cola<NodoDeHeap<T>*>();
}


/*
 * El ingreso de un dato implica varias cosas:
 * 1) Se chequea si el dato ya existe, en cuyo caso se suma 1 en *repeticiones* al nodo en cuestion y no se agrega uno
 * nuevo.
 * 2) Si el dato no existe, se inserta "al final".
 * 3) Si sucedio 2), se ordenara "aguas arriba" y se ira swapeando de ser necesario.
*/
template <typename T>
void Heap<T>::ingresarDato(T dato) {
  // fase 1): si el dato ya existe como dato de un nodo existente, no genero un nuevo nodo
  NodoDeHeap<T>* nodoConDatoExistente = existeDato(dato, raiz); // puede ser nullptr o un nodo de heap
  if(nodoConDatoExistente) {
    nodoConDatoExistente->repeticiones++;
  } else {
    // fase 2): es necesario agregar un nuevo nodo, que tendra cierto padre
    NodoDeHeap<T>* nuevoNodo = ingresarNuevoNodo(dato);
    // fase 3): hay que ordenar aguas arriba y swapear de ser necesario
    ordenar(nuevoNodo, true);
  }
}


/*
 * Devuelve una #Pila<NodoDeHeapAbstracto<T>*>* con los items ordenados de menor a mayor. Notese que el coste de este
 * llamado, es dejar la heap inutil, es decir, su proposito -que a final de cuentas es castear esta funcion- queda
 * alcanzado.
*/
template <typename T>
Pila<NodoDeHeapAbstracto<T>*>* Heap<T>::toPila() {

  // preparacion, genero la pila a devolver
  Pila<NodoDeHeapAbstracto<T>*>* pila = new Pila<NodoDeHeapAbstracto<T>*>();
  // este ultimo nodo debe desaparecer, y debo cambiar cual es el *ultimoNodo*
  Pila<NodoDeHeap<T>*>* helperSalidaDeNodos;
  if(helperUbicNewNodos2->vacia()) {
    helperSalidaDeNodos = helperUbicNewNodos->toPila();
    // el *helperUbicNewNodos* cumplira un proposito diferente al original a partir de ahora: guarda los nodos del
    // anteultimo nivel de nodos a borrar
    helperUbicNewNodos->vaciar();
  } else {
    helperSalidaDeNodos = helperUbicNewNodos2->toPila();
  }

  while(true) {
    // la raiz actual del heap se va a la pila
    NodoDeHeapAbstracto<T>* nodoDeHeapAbstracto = new NodoDeHeapAbstracto<T>(raiz->dato, raiz->repeticiones);
    pila->apilar(nodoDeHeapAbstracto);
    // piso raiz con la informacion del ultimo nodo (shallow copy)
    raiz->dato = helperSalidaDeNodos->getTope()->dato->dato;
    raiz->repeticiones = helperSalidaDeNodos->getTope()->dato->repeticiones;
    swapsDeToPila++;

    // guardo el nodo padre del nodo a borrar
    if((helperSalidaDeNodos->getTope()->dato->padre) && !helperUbicNewNodos->contiene(helperSalidaDeNodos->getTope()->dato->padre)) {
      helperUbicNewNodos->priorizar(helperSalidaDeNodos->getTope()->dato->padre);
    }
    // el ultimo nodo debe desaparecer
    NodoDeHeap<T>* nodoABorrar = helperSalidaDeNodos->desapilar();
    // desasociar hijo del padre
    if(nodoABorrar->padre) {
      nodoABorrar->padre->hijos->desapilar();
    } else {
      // llegado a este punto, se limpio el heap
      raiz = nullptr;
    }
    delete(nodoABorrar);
    // chequeo si *helperSalidaDeNodos* quedo vacio, en cuyo casi swapeo con *helperUbicNewNodos*
    if(helperSalidaDeNodos->vacia()) {
      helperSalidaDeNodos = helperUbicNewNodos->toPila();
      helperUbicNewNodos->vaciar();
    }

    // hay que ordenar desde la nueva raiz, aguas abajo
    if(!ordenar(raiz, false)) {
      // ordenar devuelve false si no pudo ordenar dado un heap vacio
      break;
    }
  }

  // devuelvo la pila ordenada
  return pila;
}


// FUNCIONES PRIVADAS
/*
 * Devuelve un #NodoDeHeap<T>* si encuentra un nodo en this, que tenga como dato, el *dato* pasado como argumento. Si no
 * lo encuentra, devolvera un nullptr.
*/
template <typename T>
NodoDeHeap<T>* Heap<T>::existeDato(T dato, NodoDeHeap<T>* nodoReferencial) {
  NodoDeHeap<T>* helper; // este helper podra o no contener un nodo con dato *dato*
  if(nodoReferencial->dato == dato) {
    return nodoReferencial;
  } else if(dato < nodoReferencial->dato) {
    // itero por cada hijo del *nodoReferencial*, chequeo si hay match de *dato*
    Nodo<NodoDeHeap<T>*>* nodoHijo = nodoReferencial->hijos->getTope();
    while(nodoHijo) {
      // recursion
      helper = existeDato(dato, nodoHijo->dato);
      if(helper) {
        return helper;
      }
      // sera nullptr llegado al final de la pila
      nodoHijo = nodoHijo->next;
    }
  }
  // no existe el *dato*
  return nullptr;
}


// Ingresa un nuevo nodo con cierto *dato* al "final" de this.
template <typename T>
NodoDeHeap<T>* Heap<T>::ingresarNuevoNodo(T dato) {
  // genero un nuevo nodo hijo
  NodoDeHeap<T>* nuevoNodo = new NodoDeHeap<T>(dato, helperUbicNewNodos->getInicio()->dato);
  // asignar este nuevo hijo a su padre
  helperUbicNewNodos->getInicio()->dato->hijos->apilar(nuevoNodo);
  helperUbicNewNodos2->encolar(nuevoNodo);
  // chequear si este padre alcanzo su limite de aridad
  if(aridad == helperUbicNewNodos->getInicio()->dato->cantidadDeHijos()) {
    // debe ser quitado de helperUbicNewNodos, ya no puede alojar mas nodos (como hijos)
    helperUbicNewNodos->desencolar();
    // chequeo si helperUbicNewNodos quedo vacio, en cuyo caso, hay que hacer un swap
    if(helperUbicNewNodos->vacia()) {
      // swapear contenido de helperUbicNewNodos2 con helperUbicNewNodos
      Cola<NodoDeHeap<T>*>* provisorio = helperUbicNewNodos;
      helperUbicNewNodos = helperUbicNewNodos2;
      helperUbicNewNodos2 = provisorio;
    }
  }
  return nuevoNodo;
}


/*
 * Ordena el heap, de manera que asegure sus condiciones de ser heap. Esta funcion se llama cada vez que se ingresa un
 * nuevo nodo, se swapean existentes o se elimina alguno. El *nodoCausal* es el nodo que genera el llamado, y es a
 * partir del cual se comienza a ordenar. La flag *aguasArriba* determina si el ordenamiento es "aguas abajo", o "aguas
 * arriba"; esto depende del evento que causo la llamada.
*/
template <typename T>
bool Heap<T>::ordenar(NodoDeHeap<T>* nodoCausal, bool aguasArriba) {
  // un heap vacio no puede ordenarse
  if(!nodoCausal) return false;
  // si *aguasArriba*, desde hijo ubico padre
  NodoDeHeap<T>* nodoPadre = aguasArriba ? nodoCausal->padre : nodoCausal;
  if(!nodoPadre) return false;
  // cito a los hijos del padre, interesa conocer cual tiene el dato mayor (solo en el caso !aguasArriba)
  NodoDeHeap<T>* nodoMayor = nullptr;
  if(!aguasArriba) {
    Nodo<NodoDeHeap<T>*>* nodoIterado = nodoPadre->hijos->getTope();
    // si solo queda la raiz, *nodoIterado* es nullptr
    if(nodoIterado) {
      nodoMayor = nodoIterado->dato;
      nodoIterado = nodoIterado->next;
      while(nodoIterado) {
        comparaciones++;
        if(nodoIterado->dato->dato > nodoMayor->dato) {
          nodoMayor = nodoIterado->dato;
        }
        // sera nullptr llegado al final de la pila
        nodoIterado = nodoIterado->next;
      }
    }
  } else {
    nodoMayor = nodoCausal;
  }
  // obtenido el nodo mayor, lo comparo contra su padre
  comparaciones++;
  if(nodoMayor && (nodoMayor->dato > nodoPadre->dato)) {
    // si el hijo es mayor que el padre, los swapeo (shallow copy)
    T tempDato = nodoPadre->dato;
    int tempRepeticiones = nodoPadre->repeticiones;
    nodoPadre->dato = nodoMayor->dato;
    nodoPadre->repeticiones = nodoMayor->repeticiones;
    nodoMayor->dato = tempDato;
    nodoMayor->repeticiones = tempRepeticiones;
    // sumo al contador de swaps
    if(aguasArriba) {
      swapsDeOrdenarAguasArriba++;
    } else {
      swapsDeOrdenarAguasAbajo++;
    }
    // recursion
    if(aguasArriba) {
      ordenar(nodoPadre, aguasArriba);
    } else {
      ordenar(nodoMayor, aguasArriba);
    }
  }
  return true;
}

#endif
