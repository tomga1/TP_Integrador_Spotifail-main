#pragma once
#include <iostream>
#include <string>
#include "Album.h"
#include "AlbumsArchivo.h"
#include "Consola.h"
#include "Cancion.h"
#include "CancionesArchivo.h"
#include "CancionesManager.h"


class AlbumsManager
{
public:
    AlbumsManager();
    void mostrarMenu();
    bool agregarAlbum();
    void agregarCancionAAlbum();
    void listarCancionesDelAlbum(int idAlbum);
    bool editarAlbum();
    int buscarAlbum();
    int buscarPorId();
    int buscarPorNombre();
    void mostrarMenuListados();
    void listarAlbums(bool activos, bool inactivos, CancionesManager& cancionesManager);
    void mostrarAlbum();
    void cinNombre(Album &a);
    void cinEstado(Album &a);
    int generarIdAlbum();
    void exportarBackup();
    void importarBackup();

private:
    Consola _consola;
    Album _album;
    Cancion _cancion;
    AlbumsArchivo _archivoAlbums;
    AlbumsArchivo _backupAlbums;
    CancionesArchivo _cancionArchivo;
    CancionesManager _cancionesManager;

};


