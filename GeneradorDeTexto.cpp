#include <fstream>
#include <iostream>
#include <string>
#include "GeneradorDeTexto.hpp"

// Genera el archivo final, con las palabras ordenadas.
std::string GeneradorDeTexto::generarArchivoFinal(Pila<NodoDeHeapAbstracto<std::string>*>* ordenada,
                                                  std::string nombreArchivo, int aridad) {
	// generando archivo de texto
	std::ofstream archivoFinal;
	std::string nombreArchivoFinal = nombreArchivo.substr(0, (nombreArchivo.size() - 4)) + "_palabras_ordenadas_" +
    std::to_string(aridad) + ".txt";
	archivoFinal.open(nombreArchivoFinal);
	archivoFinal << "Palabra: Repeticiones" << std::endl;
	archivoFinal << "---------------------" << std::endl << std::endl;

	// recorre la pila e ingresa los datos al archivo de texto
	int contadorDePalabrasEnTotal = 0;
  int cantidadDePalabrasUnicas = ordenada->getTamano();
  std::cout << "Cantidad de palabras unicas identificadas: " << std::to_string(cantidadDePalabrasUnicas) << "." <<
    std::endl;
  NodoDeHeapAbstracto<std::string>* aux = ordenada->desapilar();
  while(aux) {
    contadorDePalabrasEnTotal += aux->repeticiones;
    archivoFinal << aux->dato << ": " << aux->repeticiones << std::endl;
    aux = ordenada->desapilar();
  }
  std::cout << "Cantidad de palabras en total: " << std::to_string(contadorDePalabrasEnTotal) << "." << std::endl;
  archivoFinal << std::endl << "Cantidad de palabras unicas: " << std::to_string(cantidadDePalabrasUnicas);
  archivoFinal << std::endl << "Cantidad de palabras en total: " << std::to_string(contadorDePalabrasEnTotal) <<
    std::endl;
  archivoFinal.close();

  return nombreArchivoFinal;
}
