#pragma once
#include <string>
#include <cstring>

class Album
{
public:
    Album();
    Album(int idAlbum, std::string & nombre, bool inactivo);
    int getIdAlbum();
    void setIdAlbum(int idAlbum);
    const char* getNombre();
    void setNombre(const std::string & nombre);
    bool getInactivo();
    void setInactivo(bool inactivo);

private:
    int _idAlbum;
    char _nombre[30];
    bool _inactivo;
};
