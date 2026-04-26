#include "lista.h"

// Constructor
template <typename T>
Lista<T>::Lista() : capacidad(10), tamanio(0){
    elementos = new T*[capacidad];
    for (int i=0; i<capacidad; ++i){
        elementos[i] = nullptr;
    }
}

// Constructor de copia (copia superficial)
template <typename T>
Lista<T>::Lista(const Lista<T>& otra)
    : capacidad(otra.capacidad), tamanio(otra.tamanio)
{
    elementos = new T*[capacidad];
    for (int i = 0; i < tamanio; ++i) {
        elementos[i] = otra.elementos[i];  // Solo copia el puntero
    }
    for (int i = tamanio; i < capacidad; ++i) {
        elementos[i] = nullptr;
    }
}

// Destructor
template <typename T>
Lista<T>::~Lista(){
    delete[] elementos;
}

// Getters
template <typename T>
int Lista<T>::obtenerCapacidad() const{
    return capacidad;
}

template <typename T>
int Lista<T>::obtenerTamanio() const{
    return tamanio;
}

template <typename T>
bool Lista<T>::estaVacia() const{
    return tamanio == 0;
}


template <typename T>
void Lista<T>::agregar(T* elemento){
    if (tamanio >= capacidad) {
        // Redimensionar
        int nuevaCapacidad = capacidad*2;// <--- doble capacidad
        T** nuevoArreglo = new T*[nuevaCapacidad];

        for (int i=0; i<capacidad; ++i){
            nuevoArreglo[i] = elementos[i];
        }
        for (int i=capacidad; i<nuevaCapacidad; ++i) {
            nuevoArreglo[i] = nullptr;
        }

        delete[] elementos;
        elementos = nuevoArreglo;
        capacidad = nuevaCapacidad;
    }

    elementos[tamanio] = elemento;
    tamanio++;
}

template <typename T>
T* Lista<T>::obtener(int indice) const{
    if (indice<0 || indice>=tamanio){
        return nullptr;  // Indice invalido
    }
    return elementos[indice];
}

template <typename T>
T* Lista<T>::operator[](int indice) const{
    return obtener(indice);
}


template <typename T>
void Lista<T>::eliminar(int indice){
    if (indice<0 || indice>=tamanio) return;

    for (int i=indice; i <tamanio-1; ++i){
        elementos[i] = elementos[i+1];
    }

    elementos[tamanio - 1] = nullptr;
    tamanio--;
}

template <typename T>
void Lista<T>::limpiar(){
    for (int i = 0; i < tamanio; ++i) {
        elementos[i] = nullptr;
    }
    tamanio = 0;
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra)
{
    if (this == &otra) return *this;

    // Liberar arreglo actual (NO los objetos)
    delete[] elementos;

    // Copiar nueva
    capacidad = otra.capacidad;
    tamanio = otra.tamanio;
    elementos = new T*[capacidad];

    for (int i = 0; i < tamanio; ++i) {
        elementos[i] = otra.elementos[i];  // Solo copia punteros
    }
    for (int i = tamanio; i < capacidad; ++i) {
        elementos[i] = nullptr;
    }

    return *this;
}
