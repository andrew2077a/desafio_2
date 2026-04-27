#include "libreria.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void lector_archivo(string nombre_archivo){
    ifstream archivo(nombre_archivo);
    string linea;
    string guardar;
    if (archivo.is_open()){
        for (int i =0;i<2;i++){
            getline(archivo,linea);
        }
        while(getline(archivo,linea)){
            guardar+=linea;
        }
        archivo.close();
    }
    else{
        cout<<"El archivo no se pudo abrir"<<endl;
    }


}

/*
    lector_archivo("C:\\Users\\gisel\\OneDrive\\Escritorio\\practi_c++\\fina\\desafio_2\\selecciones_clasificadas_mundial.csv");


}

*/
