#ifndef LISTA_H
#define LISTA_H


// Definimos una plantilla (template) para que la lista pueda guardar cualquier tipo de dato (T)
template <typename T>
class Lista {
private:
    // ATRIBUTOS PRIVADOS (Encapsulamiento)
    T** elementos;    // Puntero doble: es un arreglo que guarda direcciones de memoria (punteros) de tipo T
    int capacidad;    // Espacio total reservado en la memoria RAM
    int tamanio;      // Cantidad de elementos reales almacenados actualmente

    // MÉTODO PRIVADO: Solo la clase puede llamarlo para crecer cuando se llena
    void expandir() {
        capacidad += 5;                // Aumentamos el cupo de la lista de 5 en 5 (eficiencia)
        T** nuevo = new T*[capacidad]; // Solicitamos un nuevo bloque de memoria más grande

        // Copiamos los punteros que ya teníamos al nuevo espacio
        for (int i = 0; i < tamanio; i++) {
            nuevo[i] = elementos[i];
        }

        delete[] elementos; // Liberamos la memoria del arreglo viejo para evitar fugas (memory leaks)
        elementos = nuevo;  // Apuntamos al nuevo bloque de memoria
    }

public:
    // CONSTRUCTOR: Se ejecuta al crear el objeto (Nombre según diagrama: ListaT)
    Lista() {
        capacidad = 10;                // Empezamos con espacio para 10 elementos
        tamanio = 0;                   // Inicialmente no hay nada guardado
        elementos = new T*[capacidad]; // Reservamos el primer bloque de memoria dinámica
    }

    // DESTRUCTOR: Se ejecuta al destruir el objeto para limpiar la RAM
    ~Lista() {
        delete[] elementos; // Borramos el arreglo de punteros (pero no los objetos apuntados)
    }

    // MÉTODO AGREGAR: Inserta un nuevo puntero al final de la lista
    void agregar(T* valor) {
        if (tamanio == capacidad) {
            expandir(); // Si ya no hay espacio, crecemos la lista
        }
        elementos[tamanio] = valor; // Guardamos la dirección del objeto en la última posición
        tamanio++;                  // Incrementamos el contador de elementos
    }

    // MÉTODO OBTENER: Devuelve una referencia al objeto en la posición 'indice'
    T& obtener(int indice) {
        // Retornamos el contenido (* descarta el puntero) para trabajar con el objeto directamente
        return *elementos[indice];
    }

    // MÉTODO ELIMINAR: Quita un elemento y mueve los demás para no dejar huecos
    void eliminar(int indice) {
        if (indice >= 0 && indice < tamanio) {
            // Desplazamos todos los elementos una posición a la izquierda
            for (int i = indice; i < tamanio - 1; i++) {
                elementos[i] = elementos[i + 1];
            }
            tamanio--; // Ahora tenemos un elemento menos
        }
    }

    // MÉTODO TAMANIO: Retorna cuántos elementos hay (es const porque no modifica la lista)
    int obtenerTamanio() const {
        return tamanio;
    }

    // SOBRECARGA DEL OPERADOR []: Permite usar la lista como un arreglo: lista[i]
    T& operator[](int indice) {
        return *elementos[indice]; // Retorna la referencia al objeto solicitado
    }
};


#endif // LISTA_H
