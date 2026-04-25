#ifndef LISTA_H
#define LISTA_H

template <typename T>
class Lista
{
private:
    T** elementos;
    int capacidad;
    int tamanio;

    // Prohibir copia profunda (solo observadora)
    Lista(const Lista<T>&);
    Lista<T>& operator=(const Lista<T>&);

public:
    //Constructor
    Lista();

    //Destructor
    ~Lista();

    //Getter
    int obtenerCapacidad() const;
    int obtenerTamanio() const;
    bool estaVacia() const;

    //Setter
    void agregar(T* elemento);
    T* obtener(int indice) const;
    T* operator[](int indice) const;

    void eliminar(int indice);
    void limpiar();
};


#endif
