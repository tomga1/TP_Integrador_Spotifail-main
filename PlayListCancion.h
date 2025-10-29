#pragma once

class PlaylistCancion
{
public:
    PlaylistCancion();
    PlaylistCancion(int idPlaylist, int idCancion, int orden, bool inactivo);
    int getIdPlaylist();
    void setIdPlaylist(int idPlaylist);
    int getIdCancion();
    void setIdCancion(int idCancion);
    int getOrden();
    void setOrden(int orden);
    bool getInactivo();
    void setInactivo(bool inactivo);

private:
    int _idPlaylist;
    int _idCancion;
    int _orden;
    bool _inactivo;
};
