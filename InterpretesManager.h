#pragma once
#include "InterpretesArchivo.h"
#include "Consola.h"
#include "Interprete.h"
#include "GenerosArchivo.h"

class InterpretesManager {
public:
    InterpretesManager();
    void mostrarMenu();
    bool agregarInterprete();
    bool editarInterprete();
    int buscarInterprete();
    void mostrarMenuListados();
    void listarInterpretes(bool activos, bool inactivos);
    void mostrarInterprete();
    void cinNombre(Interprete &i);
    void cinEstado(Interprete &i);
    void cinGenero(Interprete &i);
    void exportarBackup();
    void importarBackup();
    int generarIdInterprete();

private:
    InterpretesArchivo _archivoInterpretes;
    InterpretesArchivo _backupInterpretes;
    Consola _consola;
    Interprete _interprete;
    GenerosArchivo _generosArchivo;

};
