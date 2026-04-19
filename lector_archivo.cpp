#include "libreria.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void lector_archivo(string nombre_archivo){
    ifstream archivo(nombre_archivo);
    string linea;

    if (archivo.is_open()){
        while(getline(archivo,linea)){
            cout<<linea<<endl;
        }
        archivo.close();
    }
    else{
        cout<<"El archivo no se pudo abrir"<<endl;
    }

}

int main(){
    lector_archivo("C:\\Users\\gisel\\OneDrive\\Escritorio\\practi_c++\\fina\\desafio_2\\selecciones_clasificadas_mundial.csv");
    return 0;

}
