#pragma once

class AlbumCancion
{
public:
    AlbumCancion();
    AlbumCancion(int idAlbum, int idCancion, int orden, bool inactivo);

    int getIdAlbum();
    void setIdAlbum(int idAlbum);

    int getIdCancion();
    void setIdCancion(int idCancion);

    int getOrden();
    void setOrden(int orden);

    bool getInactivo();
    void setInactivo(bool inactivo);

private:
    int _idAlbum;
    int _idCancion;
    int _orden;
    bool _inactivo;
};
