#pragma once
#include "Cancion.h"
#include "CancionesArchivo.h"
#include "Consola.h"
#include "GenerosManager.h"
#include "InterpretesManager.h"
#include "Album.h"
#include "AlbumsArchivo.h"

class CancionesManager {
public:
    CancionesManager();
    void mostrarMenu();
    bool agregarCancion();
    bool editarCancion();
    int buscarCancion();
    void mostrarMenuListados();
    void listarCanciones(bool activas, bool inactivas);
    void listarCancionesPorAlbum(int idAlbum);
    void mostrarCancion();
    void exportarBackup();
    void importarBackup();
    void cinTitulo(Cancion &c);
    void cinAutor(Cancion &c);
    void cinIdInterprete(Cancion &c);
    void cinIdAlbum(Cancion &c);
    void cinIdGenero(Cancion &c);
    void cinFechaPublicacion(Cancion &c);
    void cinEstado(Cancion &c);
    int generarIdCancion();
    int buscarPorId();
    int buscarPorTitulo();
    int buscarPorAutor();

private:
    CancionesArchivo _archivoCanciones;
    CancionesArchivo _backupCanciones;
    Consola _consola;
    Cancion _cancion;
    Album _album;
    AlbumsArchivo _albumArchivos;
    GenerosArchivo _generosArchivo;
    InterpretesArchivo _interpretesArchivo;

};
