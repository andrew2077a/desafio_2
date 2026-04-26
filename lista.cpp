#include "lista.h"

template <typename T>
Lista<T>::Lista() : capacidad(10), tamanio(0) {
    elementos = new T*[capacidad];
    for (int i = 0; i < capacidad; ++i) elementos[i] = nullptr;
}

template <typename T>
Lista<T>::Lista(const Lista<T>& otra)
    : capacidad(otra.capacidad), tamanio(otra.tamanio) {
    elementos = new T*[capacidad];
    for (int i = 0; i < tamanio; ++i)
        elementos[i] = otra.elementos[i];
    for (int i = tamanio; i < capacidad; ++i)
        elementos[i] = nullptr;
}

template <typename T>
Lista<T>::~Lista() {
    delete[] elementos;
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra) {
    if (this == &otra) return *this;
    delete[] elementos;
    capacidad = otra.capacidad;
    tamanio = otra.tamanio;
    elementos = new T*[capacidad];
    for (int i = 0; i < tamanio; ++i)
        elementos[i] = otra.elementos[i];
    for (int i = tamanio; i < capacidad; ++i)
        elementos[i] = nullptr;
    return *this;
}

template <typename T>
int Lista<T>::obtenerCapacidad() const { return capacidad; }

template <typename T>
int Lista<T>::obtenerTamanio() const { return tamanio; }

template <typename T>
bool Lista<T>::estaVacia() const { return tamanio == 0; }

template <typename T>
void Lista<T>::agregar(T* elemento) {
    if (tamanio >= capacidad) {
        int nuevaCapacidad = capacidad * 2;
        T** nuevoArreglo = new T*[nuevaCapacidad];
        for (int i = 0; i < capacidad; ++i)
            nuevoArreglo[i] = elementos[i];
        for (int i = capacidad; i < nuevaCapacidad; ++i)
            nuevoArreglo[i] = nullptr;
        delete[] elementos;
        elementos = nuevoArreglo;
        capacidad = nuevaCapacidad;
    }
    elementos[tamanio] = elemento;
    ++tamanio;
}

template <typename T>
T* Lista<T>::obtener(int indice) const {
    if (indice < 0 || indice >= tamanio) return nullptr;
    return elementos[indice];
}

template <typename T>
T* Lista<T>::operator[](int indice) const {
    return obtener(indice);
}

template <typename T>
T*& Lista<T>::operator[](int indice) {
    if (indice < 0 || indice >= tamanio) {
        static T* nulo = nullptr;
        return nulo;
    }
    return elementos[indice];
}

template <typename T>
T* Lista<T>::operator[](int indice) const {
    if (indice<0 || indice>=tamanio) return nullptr;
    return elementos[indice];
}

template <typename T>
T*& Lista<T>::operator[](int indice) {
    if (indice<0 || indice>=tamanio) {
        static T* nulo = nullptr;
        return nulo;
    }
    return elementos[indice];
}
