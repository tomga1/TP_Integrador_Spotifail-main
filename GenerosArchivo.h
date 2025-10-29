#pragma once
#include <string>
#include <iostream>
#include "Genero.h"

class GenerosArchivo {
public:
    GenerosArchivo();
    GenerosArchivo(const std::string &ruta);
    void setRuta(const std::string &ruta);
    std::string getRuta() const;
    bool escribir(Genero &reg);
    bool sobrescribir(Genero &reg, int indice);
    Genero leer(int indice);
    int buscarPorId(int idGenero);
    int buscarPorNombre(const std::string &nombre);
    int contarRegistros();
    void crearArchivoVacio();
    Genero leerPorId(int idGenero);

private:
    std::string _ruta;
};
