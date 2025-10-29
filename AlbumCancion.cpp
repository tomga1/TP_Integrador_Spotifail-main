#include "AlbumCancion.h"

AlbumCancion::AlbumCancion()
{
    setIdAlbum(1);
    setIdCancion(1);
    setOrden(1);
    setInactivo(false);
}

AlbumCancion::AlbumCancion(int idAlbum, int idCancion, int orden, bool inactivo)
{
    setIdAlbum(idAlbum);
    setIdCancion(idCancion);
    setOrden(orden);
    setInactivo(inactivo);
}

int AlbumCancion::getIdAlbum() { return _idAlbum; }
void AlbumCancion::setIdAlbum(int idAlbum) { _idAlbum = idAlbum; }

int AlbumCancion::getIdCancion() { return _idCancion; }
void AlbumCancion::setIdCancion(int idCancion) { _idCancion = idCancion; }

int AlbumCancion::getOrden() { return _orden; }
void AlbumCancion::setOrden(int orden) { _orden = orden; }

bool AlbumCancion::getInactivo() { return _inactivo; }
void AlbumCancion::setInactivo(bool inactivo) { _inactivo = inactivo; }
