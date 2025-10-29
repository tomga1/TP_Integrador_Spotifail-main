#include "PlaylistCancion.h"

PlaylistCancion::PlaylistCancion()
{
    setIdPlaylist(1);
    setIdCancion(1);
    setOrden(1);
    setInactivo(false);
}

PlaylistCancion::PlaylistCancion(int idPlaylist, int idCancion, int orden, bool inactivo)
{
    setIdPlaylist(idPlaylist);
    setIdCancion(idCancion);
    setOrden(orden);
    setInactivo(inactivo);
}

int PlaylistCancion::getIdPlaylist() { return _idPlaylist; }
void PlaylistCancion::setIdPlaylist(int idPlaylist) { _idPlaylist = idPlaylist; }

int PlaylistCancion::getIdCancion() { return _idCancion; }
void PlaylistCancion::setIdCancion(int idCancion) { _idCancion = idCancion; }

int PlaylistCancion::getOrden() { return _orden; }
void PlaylistCancion::setOrden(int orden) { _orden = orden; }

bool PlaylistCancion::getInactivo() { return _inactivo; }
void PlaylistCancion::setInactivo(bool inactivo) { _inactivo = inactivo; }
