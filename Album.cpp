#include "Album.h"

Album::Album()
{
    setIdAlbum(1);
    setNombre("N/A");
    setInactivo(false);
}

Album::Album(int idAlbum, std::string & nombre, bool inactivo)
{
    setIdAlbum(idAlbum);
    setNombre(nombre);
    setInactivo(inactivo);
}

int Album::getIdAlbum() { return _idAlbum; }
void Album::setIdAlbum(int idAlbum) { _idAlbum = idAlbum; }

const char* Album::getNombre() { return _nombre; }
void Album::setNombre(const std::string & nombre) { strcpy(_nombre, nombre.c_str()); }

bool Album::getInactivo() { return _inactivo; }
void Album::setInactivo(bool inactivo) { _inactivo = inactivo; }
