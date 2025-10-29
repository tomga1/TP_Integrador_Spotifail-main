#pragma once
#include <string>
#include <cstring>
#include "Fecha.h"

class Cancion
{
public:
    Cancion();
    Cancion(int idCancion, std::string &titulo, std::string &autor,
            int idInterprete, int idGenero, int idAlbum, Fecha fechaPublicacion, bool inactivo);
    int getIdCancion();
    void setIdCancion(int idCancion);
    const char* getTitulo();
    void setTitulo(const std::string &titulo);
    const char* getAutor();
    void setAutor(const std::string &autor);
    int getIdInterprete();
    void setIdInterprete(int idInterprete);
    int getIdGenero();
    void setIdGenero(int idGenero);
    int getIdAlbum();
    void setIdAlbum(int idAlbum);
    Fecha getFechaPublicacion();
    void setFechaPublicacion(Fecha fechaPublicacion);
    bool getInactivo();
    void setInactivo(bool inactivo);

private:
    int _idCancion;
    char _titulo[30];
    char _autor[30];
    int _idInterprete;
    int _idGenero;
    int _idAlbum;
    Fecha _fechaPublicacion;
    bool _inactivo;
};
