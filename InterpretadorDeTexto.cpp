#include "InterpretadorDeTexto.hpp"

/*
 * Lee e interpreta el archivo de interes *st*. La *aridad* del #Heap a utilizar para contener sus palabras es de
 * importancia.
*/
Heap<std::string>* InterpretadorDeTexto::interpretarTexto(std::string st, int aridad) {

  Heap<std::string>* heap;
	// string temporal para cada palabra
	std::string palabra = "";

	bool heapCreado = false;
	
	// loop separando palabras
	for(std::string::size_type i = 0; i < st.size(); i++) {
		
		// si es letra,la guarda en palabra
		if(std::isalpha(st[i])) {
			// a minuscula
			st[i] = std::tolower(st[i]);
			// agregar letra a palabra
			palabra = palabra + st[i];
		}
		// si no es letra, hay corte entre palabras
		else {
			// revisar si el caracter anterior era letra: una palabra acaba de terminar
			if(std::isalpha(st[i-1])) {
				// enviar palabra completa al heap
				// si es la primera palabra, crear heap
				if(!heapCreado) {
					// crear heap
          heap = new Heap<std::string>(aridad, palabra);
          heapCreado = true;
				}
				// si es la segunda o más, agregar al heap
        else {
          heap->ingresarDato(palabra);
				}
        palabra = "";
			}
		}
	}
	// si quedo palabra remanente por agregar, hacerlo
	if(!palabra.empty()) {
    heap->ingresarDato(palabra);
	}

	return heap;
}
