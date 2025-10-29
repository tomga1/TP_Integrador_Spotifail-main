#pragma once
#include <string>
#include <iostream>
#include "Album.h"

class AlbumsArchivo
{
    public:
    AlbumsArchivo();
    AlbumsArchivo(const std::string &ruta);
    void setRuta(const std::string &ruta);
    std::string getRuta() const;
    bool escribir(Album &reg);
    bool sobrescribir(Album &reg, int indice);
    Album leer(int indice);
    Album leerPorId(int idAlbum);
    int buscarPorId(int idAlbum);
    int buscarPorNombre(const std::string & nombre);
    int contarRegistros();
    void crearArchivoVacio();

    private:
    std::string _ruta;
};

