#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista
{
private:
    T** elementos;     // Arreglo dinamico de punteros a T
    int capacidad;     // Tamaño max
    int tamanio;       // Cantidad de elementos

public:
    // Constructor
    Lista();

    // Constructor de copia
    Lista(const Lista<T>& otra);

    // Destructor
    ~Lista();

    // Consultas básicas
    int obtenerCapacidad() const;
    int obtenerTamanio() const;
    bool estaVacia() const;

    void agregar(T* elemento);
    T* obtener(int indice) const;
    T* operator[](int indice) const;  

    void eliminar(int indice);
    void limpiar(); 

    // Operador de asignacion
    Lista<T>& operator=(const Lista<T>& otra);

};

#include "lista.cpp"

#endif
