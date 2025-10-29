#pragma once
#include <string>
#include <iostream>
#include "Cancion.h"

class CancionesArchivo
{
public:
    CancionesArchivo();
    CancionesArchivo(const std::string &path);
    void setPath(const std::string &path);
    std::string getPath() const;
    bool escribir(Cancion &reg);
    bool sobreEscribir(Cancion &reg, int index);
    Cancion leer(int index);
    Cancion leerPorId(int id);
    bool sobreEscribirPorId(Cancion &reg, int id);
    int buscarPorId(int id);
    int getCantidadRegistros();
    void crearArchivoVacio();

private:
    std::string _path;
};
