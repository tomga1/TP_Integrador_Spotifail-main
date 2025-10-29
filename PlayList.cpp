#include "Playlist.h"

Playlist::Playlist()
{
    setIdPlaylist(1);
    setIdSuscriptor(1);
    setNombre("N/A");
    setFechaCreacion(Fecha());
    setInactivo(false);
}

Playlist::Playlist(int idPlaylist, int idSuscriptor, std::string & nombre, Fecha fechaCreacion, bool inactivo)
{
    setIdPlaylist(idPlaylist);
    setIdSuscriptor(idSuscriptor);
    setNombre(nombre);
    setFechaCreacion(fechaCreacion);
    setInactivo(inactivo);
}

int Playlist::getIdPlaylist() { return _idPlaylist; }
void Playlist::setIdPlaylist(int idPlaylist) { _idPlaylist = idPlaylist; }

int Playlist::getIdSuscriptor() { return _idSuscriptor; }
void Playlist::setIdSuscriptor(int idSuscriptor) { _idSuscriptor = idSuscriptor; }

const char* Playlist::getNombre() { return _nombre; }
void Playlist::setNombre(const std::string & nombre) { strcpy(_nombre, nombre.c_str()); }

Fecha Playlist::getFechaCreacion() { return _fechaCreacion; }
void Playlist::setFechaCreacion(Fecha fechaCreacion) { _fechaCreacion = fechaCreacion; }

bool Playlist::getInactivo() { return _inactivo; }
void Playlist::setInactivo(bool inactivo) { _inactivo = inactivo; }
