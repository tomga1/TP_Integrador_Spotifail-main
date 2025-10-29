#pragma once
#include "GenerosArchivo.h"
#include "Consola.h"
#include "Genero.h"

class GenerosManager {
public:
    GenerosManager();
    void mostrarMenu();
    bool agregarGenero();
    bool editarGenero();
    int buscarGenero();
    void mostrarMenuListados();
    void listarGeneros(bool activos, bool inactivos);
    void mostrarGenero();
    void cinNombre(Genero &g);
    void cinEstado(Genero &g);
    void exportarBackup();
    void importarBackup();
    int generarIdGenero();

private:
    GenerosArchivo _archivoGeneros;
    GenerosArchivo _backupGeneros;
    Consola _consola;
    Genero _genero;

};
