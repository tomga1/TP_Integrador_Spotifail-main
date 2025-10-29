#pragma once
#include <string>
#include <cstring>
#include "Fecha.h"

class Playlist
{
public:
    Playlist();
    Playlist(int idPlaylist, int idSuscriptor, std::string & nombre, Fecha fechaCreacion, bool inactivo);
    int getIdPlaylist();
    void setIdPlaylist(int idPlaylist);
    int getIdSuscriptor();
    void setIdSuscriptor(int idSuscriptor);
    const char* getNombre();
    void setNombre(const std::string & nombre);
    Fecha getFechaCreacion();
    void setFechaCreacion(Fecha fechaCreacion);
    bool getInactivo();
    void setInactivo(bool inactivo);

private:
    int _idPlaylist;
    int _idSuscriptor;
    char _nombre[30];
    Fecha _fechaCreacion;
    bool _inactivo;
};
