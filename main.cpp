#include <iostream>
#include <string>
#include <fstream>
#include "main.hpp"
#include "GeneradorDeTexto.hpp"

int main(){
  ejecutarBienvenida();
	// ejecutar el pedido de aridad
	int aridad = obtenerAridad();
	// ejecutar el pedido de ruta a archivo txt
	std::string ruta = obtenerRuta();
  // extraigo el texto del archivo
	std::string texto = obtenerTexto(ruta);
	if(texto.empty()) {
    std::cout << "La ruta ingresada es invalida o el archivo no contiene texto alguno." << std::endl;
    return 0;
	}

	InterpretadorDeTexto interpretadorDeTexto;
	// obtener un tree-heap con las palabras
	Heap<std::string>* heap = interpretadorDeTexto.interpretarTexto(texto, aridad);

	// obtener una pila con las palabras ordenadas
	Pila<NodoDeHeapAbstracto<std::string>*>* pila = heap->toPila();

	// presentar palabras ordenadas
	GeneradorDeTexto generadorDeTexto;
	std::string nombreArchivoFinal = generadorDeTexto.generarArchivoFinal(pila, ruta, aridad);
  std::cout << "El archivo con sus palabras ordenadas se encuentra en: \"" << nombreArchivoFinal << "\"." << std::endl;

	// presentar cantidad de comparaciones realizadas
  imprimirComparaciones(heap);

	return 0;
}



void ejecutarBienvenida() {
  std::cout << std::endl << "ORDENADOR Y CONTABILIZADOR DE PALABRAS" << std::endl;
  std::cout << "======================================" << std::endl << std::endl;
  std::cout << "Bienvenido/a. ";
}


// No se espera mala intencion del usuario, se espera ingresado un valor mayor a 0 como aridad.
int obtenerAridad() {
	std::cout << "Ingrese la aridad(del heap a utilizar) deseada: ";
	int aridad;
	std::cin >> aridad;
	return aridad;
}


std::string obtenerRuta() {
  std::string s;
  std::cout << "Ingrese la ruta de su archivo *.txt: ";
  std::getline(std::cin >> std::ws, s);
  std::cout << std::endl;
  return s;
}


// Obtiene el texto a procesar, a partir del contenido de cierto archivo ubicado en *ruta*.
std::string obtenerTexto(std::string ruta) {
	std::ifstream archivo;
  std::string texto;

  // abre el archivo
	archivo.open(ruta);
  if(archivo.fail()) {
    // el archivo no existe, devuelvo string vacia
    return texto;
  }

	// extraer string
	std::string linea;
  while(!archivo.eof()){
    std::getline(archivo, linea);
    texto += linea;
    // se prescinde de los saltos de linea, irrelevantes para el proposito final
    texto += " ";
  }
	
  archivo.close();
	return texto;
}


// Imprimir el numero de comparaciones realizadas.
void imprimirComparaciones(Heap<std::string>* heap) {
	std::cout << "La cantidad de intercambios(swaps) realizados durante todo el proceso fueron: " << heap->swapsTotales()
	  << "; de los cuales " << heap->swapsDeOrdenarAguasArriba <<
	  " ocurrieron durante los re-ordenamientos por nuevo ingreso de nodo; y " <<
	  (heap->swapsDeOrdenarAguasAbajo + heap->swapsDeToPila) << " ocurrieron durante el llamado a #toPila()." <<
	  " Por otro lado, la cantidad de comparaciones realizadas fueron " << heap->comparaciones << "." <<
	  " Sabemos por observacion del codigo que el peso swap vs comparacion es aproximadamente de 1:6, por lo tanto" <<
	  " concluimos que un valor comparativo de costo computacional es aproximadamente " <<
	  (heap->swapsTotales() + (heap->comparaciones / 6)) << "." << std::endl;
}
