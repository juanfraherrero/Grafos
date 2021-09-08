#include "Grafo.h"

#include "iostream"

using namespace std;

template <typename C>
ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
	// Recorremos todos los vertices
	list<int> vertices;
	grafo.devolver_vertices(vertices);
	list<int>::iterator v = vertices.begin();
	while (v != vertices.end()) {
		salida << "    " << *v << "\n";
		// Recorremos todos los adyacentes de cada vertice
		list<typename Grafo<C>::Arco> adyacentes;
		grafo.devolver_adyacentes(*v, adyacentes);
		typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
		while (ady != adyacentes.end()) {
			salida << "    " << *v << "-> " << ady->devolver_adyacente() << " (" << ady->devolver_costo() << ")\n";
			ady++;
		}
		v++;
	}
	return salida;
}

int main(int argc, char **argv)
{
	Grafo<int> g;

	/*
    bool vacio;
    vacio = g.esta_vacio();
	if (vacio)
        cout <<"está vacío el grafo"<<endl;
    else
        cout <<"no está vací el grafo"<<endl;


    int longitud = g.devolver_longitud();
    cout << "longitud : "<< longitud<<endl;
    */


	// Cargamos un grafo dirigido
	// Primero los vértices
	g.agregar_vertice(1);
	g.agregar_vertice(2);
	g.agregar_vertice(3);
	g.agregar_vertice(4);
	g.agregar_vertice(5);
	g.agregar_vertice(6);
	g.agregar_vertice(7);

	// Luego los arcos
	g.agregar_arco(1, 2, 1);
	g.agregar_arco(1, 3, 1);
	g.agregar_arco(1, 4, 1);
	g.agregar_arco(2, 6, 2);
	g.agregar_arco(3, 5, 3);
	g.agregar_arco(4, 7, 4);
	g.agregar_arco(5, 6, 5);
	Grafo<int> g2(g);
	//g.agregar_vertice(1);     //  PREGUNTAR PORRQUE NO ME SOBREESCRIBE EL VÉRTICE 1 ????


    /*
    if (g.existe_vertice(2))
        cout <<"encontró el vertice 2" << endl;
    else
        cout << "no econtró el vertice 2"<<endl;;
	g.eliminar_vertice(2);
	*/

	/*
    vacio = g.esta_vacio();
	if (vacio)
        cout <<"está vacío el grafo"<<endl;
    else
        cout <<"no está vací el grafo"<<endl;


    longitud = g.devolver_longitud();
    cout << "longitud : "<< longitud<<endl;

    */

    /*
    bool vacio;
    vacio = g.existe_arco(2,6);
	if (vacio)
        cout <<"existe el arco"<<endl;
    else
        cout <<"no existe el arco"<<endl;

    cout << "el costo del arco es: " << g.costo_arco(4,7)<<endl;
    g.modificar_costo_arco(4,7,10);
    cout << "el costo del arco es: " << g.costo_arco(4,7)<<endl;
    */


	cout<< "-----------------------"<<endl <<endl<<endl;

	// Mostramos el grafo
	cout << "Estructura del grafo:\n" << g << "\n";
	cout<< "-----------------------"<<endl <<endl<<endl;

	// Mostramos el grafo
	cout << "Estructura del grafo:\n" << g2 << "\n";

	return 0;
}
