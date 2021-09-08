#ifndef GRAFO_H_
#define GRAFO_H_
#include "iostream"
#include <list>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <assert.h>

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
        {
            friend class Grafo;
            public:
                Arco();     //era necesario el destructor aunque no te sirva aquí?
                Arco(int adyacente, const C & costo);
                int devolver_adyacente() const;
                const C & devolver_costo() const;
                bool operator < (const Arco & Otro_Arco) const;
            private:
                int vertice;
                C costo;
        }; // class Arco


public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de vértices es cero
	bool esta_vacio() const;

	// Indica la cantidad de vértices del grafo
	int devolver_longitud() const;

	bool existe_vertice(int vertice) const;

	bool existe_arco(int origen, int destino) const;

	// PRE CONDICION: existe_arco(origen, destino)
	// el usuario debe llamar con un arco válido o se termina el programa
	const C & costo_arco(int origen, int destino) const;

	void devolver_vertices(list<int> & vertices) const;

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

	void agregar_vertice(int vertice);

	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	// el usuario debe llamar con un arco válido o se termina el programa
	void modificar_costo_arco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	//puede haber más de una arco
	void agregar_arco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);

	void vaciar();

	int cantida_vertices() const;

private:
	/*
	 * Definir la estructura interna
	 */

	 map< int, list<Arco> > _Grafo;

}; // class Grafo


/*
 * Arco
 */

 /*
 *  v = cantidad de vertices totales de un grafo
 *  a = promedio de adyacentes a un vertice
 *
 */

template <typename C> Grafo<C>::Arco::Arco()
{
}

template <typename C> //O(1)
Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C> //O(1)
int Grafo<C>::Arco::devolver_adyacente() const
{
 return this->vertice;
}

template <typename C> //O(1)
const C & Grafo<C>::Arco::devolver_costo() const
{
    return this->costo;
}

template <typename C> //O(1)
bool Grafo<C>::Arco::operator < (const Arco & Otro_Arco) const
{
    return (this->vertice < Otro_Arco.vertice);
}


/*
 * Grafo
 */

template <typename C>
Grafo<C>::Grafo()
{
}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> //O(1)
Grafo<C>::Grafo(const Grafo & otroGrafo)
{
    this->operator = (otroGrafo);
}

template <typename C> //O(1)
Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{
    this->_Grafo = otroGrafo._Grafo; //PREGUNTAR PORQUE NO ES THIS = OTROGRAFO;  ya que si tiene otro atributo el grafo ese no se copia
    return * this;
}

template <typename C> //O(1)
bool Grafo<C>::esta_vacio() const
{
    return this->_Grafo.empty();//O(1)
}

template <typename C> //O(1)
int Grafo<C>::devolver_longitud() const
{
    return _Grafo.size(); //devuelve exactamente la cantidad de claves
}

template <typename C> //O(log(v))
bool Grafo<C>::existe_vertice(int vertice) const
{
    if (this->_Grafo.find(vertice) == this->_Grafo.end() ) //O(log(v))
        return false;
    else
        return true;
}

template <typename C> // MAX { O(log(v)), O(a) }
bool Grafo<C>::existe_arco(int origen, int destino) const
{
    bool existe = false;
    typename map<int, list<Arco>>::const_iterator it = this->_Grafo.find(origen); //O(log(v))
    if (it !=  this->_Grafo.end() )
        {
            typename list<Arco>::const_iterator itL = it->second.begin();
            while (( !existe ) && ( itL != it->second.end() ) )     //O(a)
                {
                    if (itL->devolver_adyacente() == destino)
                        existe = true;
                    itL++;
                }

        }


    return existe;
}

template <typename C>   // MAX { O(log(v)), O(a) }
const C & Grafo<C>::costo_arco(int origen, int destino) const
{

  //debe llamarse a esta función cn un arco válido
  assert(existe_arco(origen,destino));

    typename map<int, list<Arco>>::const_iterator it = this->_Grafo.find(origen); //O(log(v))
    typename list<Arco>::const_iterator itlist = it->second.begin();

    while (itlist !=  it->second.end() )   //O(a)
        {
            if (itlist->vertice == destino)
                return itlist->costo;

            itlist++;
        }
}

template <typename C> //O(v)
void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    typename map<int, list<Arco>>::const_iterator it = this->_Grafo.begin();
    while (it != this->_Grafo.end()) //O(v)
    {
        vertices.push_back(it->first); //O(1)
        it++;
    }
}

template <typename C> // MAX { O(log(v)), O(a) }
void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int, list<Arco>>::const_iterator it = this->_Grafo.find(origen); //O(log(v))
    if (it !=  this->_Grafo.end() )
        {
            typename list<Arco>::const_iterator itL = it->second.begin();
            while (itL != it->second.end())     //O(a)
                {
                    adyacentes.push_back(*itL);
                    itL++;
                }

        }


}

template <typename C> // O(log(v))
void Grafo<C>::agregar_vertice(int vertice)
{
    assert( !existe_vertice(vertice) ); //no me permite agregar más de un vértice igual

    //_Grafo[vertice]; //es válido?
    list<Arco> lista;
    this->_Grafo.insert({vertice,lista}); //pair<int,list<Arco>>(vertice,lista) así también

}

template <typename C> //O(v.a)
void Grafo<C>::eliminar_vertice(int vertice)
{
    if ( existe_vertice(vertice) )
    {
        typename map<int,list<Arco>>::iterator itmap = this->_Grafo.begin();
        while (itmap != this->_Grafo.end()) //O(v)
        {
            if (itmap->first == vertice)
                {
                    typename map<int,list<Arco>>::iterator itmapaux;
                    itmapaux = itmap;
                    //itmapaux->second.erase();     //preguntar si esto es necesario
                    //itmapaux = itmap;
                    itmap++; //lo cambio antes de borrar la posición    //preguntar por las dudas
                    _Grafo.erase(itmapaux); //O(1)
                }
            else
                {
                    typename list<Arco>::iterator itlist = itmap->second.begin();
                    while (itlist != itmap->second.end()) //O(a)
                    {
                        if (itlist->vertice == vertice)
                        {
                            typename list<Arco>::iterator itlistaux;
                            itlistaux = itlist;
                            itlist++;
                            itmap->second.erase(itlistaux);  //O(1)
                        }
                        else
                            itlist++;
                    }

                    itmap ++;
                }

        }

    }
    else   cout << "no se eliminó ningún vértice porque no se encontró ese vértice" << endl;

}

template <typename C>   //O(v.a)
void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
    //debe llamarse a esta función cn un arco válido
    assert(existe_arco(origen,destino));

    typename map<int, list<Arco>>::iterator it = this->_Grafo.find(origen); //O(log(v))
    typename list<Arco>::iterator itlist = it->second.begin();
    bool modificado = false;
    while (!modificado && itlist !=  it->second.end() )   //O(a)
        {
            if (itlist->vertice == destino)
            {
                itlist->costo = costo;
                modificado = true;
            }
            itlist++;
        }

}

template <typename C> //O(log(v))
void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    assert(!existe_arco(origen,destino));   //si quiero que no se repitan le pongo esto y listo
    assert((existe_vertice(origen))&&(existe_vertice(destino))); //o le pongo un assert?

    typename map<int, list<Arco>>::iterator it = this->_Grafo.find(origen); //O(log(v))
    it->second.push_back(Arco(destino, costo)); //O(1)
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    if ( !this->existe_vertice(origen))  //O(log(v))
    {
        typename map<int,list<Arco>>::iterator itmap = this->_Grafo.find(origen);//O(log(v))
        typename list<Arco>::iterator itlist = itmap->second.begin();
        bool eliminado = false;
        while ( (!eliminado) && (itlist != itmap->second.end())) //O(a)
        {
            if (itlist->vertice == destino)
            {
                itmap->second.erase(itlist);  //O(1)
                eliminado = true;
            }
            itlist++;

        }

    }
    else   cout << "no se encontró ese vértice" << endl;
}

template <typename C> void Grafo<C>::vaciar()
{
    _Grafo.clear(); //O(v)   //o tambien es por la cantidad de adyacentes por la eliminación de las listas?
}

template <typename C>
int Grafo<C>::cantida_vertices() const
{
    return _Grafo.size();
}

#endif /* GRAFO_H_ */
