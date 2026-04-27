#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista {
private:
    T* elementos;   // ← atención: T* (una sola indirección)
    int capacidad;
    int tamanio;

public:
    Lista() : capacidad(10), tamanio(0) {
        elementos = new T[capacidad];   // almacenamos objetos, no punteros
        // No es necesario inicializar a nullptr, los objetos se construyen por defecto.
    }

    Lista(const Lista<T>& otra) : capacidad(otra.capacidad), tamanio(otra.tamanio) {
        elementos = new T[capacidad];
        for (int i = 0; i < tamanio; ++i)
            elementos[i] = otra.elementos[i];
    }

    ~Lista() { delete[] elementos; }

    Lista<T>& operator=(const Lista<T>& otra) {
        if (this == &otra) return *this;
        delete[] elementos;
        capacidad = otra.capacidad;
        tamanio = otra.tamanio;
        elementos = new T[capacidad];
        for (int i = 0; i < tamanio; ++i)
            elementos[i] = otra.elementos[i];
        return *this;
    }

    int obtenerCapacidad() const { return capacidad; }
    int obtenerTamanio() const { return tamanio; }
    bool estaVacia() const { return tamanio == 0; }

    void agregar(const T& elemento) {
        if (tamanio >= capacidad) {
            int nuevaCapacidad = capacidad * 2;
            T* nuevoArreglo = new T[nuevaCapacidad];
            for (int i = 0; i < tamanio; ++i)
                nuevoArreglo[i] = elementos[i];  // copia por asignación
            delete[] elementos;
            elementos = nuevoArreglo;
            capacidad = nuevaCapacidad;
        }
        elementos[tamanio] = elemento;
        ++tamanio;
    }

    T& obtener(int indice) {
        if (indice < 0 || indice >= tamanio) throw "Índice inválido";
        return elementos[indice];
    }

    const T& obtener(int indice) const {
        if (indice < 0 || indice >= tamanio) throw "Índice inválido";
        return elementos[indice];
    }

    T& operator[](int indice) { return obtener(indice); }
    const T& operator[](int indice) const { return obtener(indice); }

    void eliminar(int indice) {
        if (indice < 0 || indice >= tamanio) return;
        for (int i = indice; i < tamanio - 1; ++i)
            elementos[i] = elementos[i + 1];
        --tamanio;
    }

    void limpiar() { tamanio = 0; }
};

#endif
