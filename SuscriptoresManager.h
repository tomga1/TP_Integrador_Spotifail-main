#pragma once
#include <iostream>
#include <string>
#include "Suscriptor.h"
#include "SuscriptoresArchivo.h"
#include "Consola.h"

class SuscriptoresManager {

public:
    SuscriptoresManager();
    void mostrarMenu();
    bool agregarSuscriptor();
    bool editarSuscriptor();
    int buscarSuscriptor();
    int buscarPorId();
    int buscarPorNombre();
    int buscarPorDni();
    void mostrarMenuListados();
    void listarSuscriptores(bool activos, bool inactivos);
    void mostrarSuscriptor();
    void cinNombre(Suscriptor &suscriptor);
    void cinApellido(Suscriptor &suscriptor);
    void cinDni(Suscriptor &suscriptor);
    void cinTelefono(Suscriptor &suscriptor);
    void cinEmail(Suscriptor &suscriptor);
    void cinFechaNacimiento(Suscriptor &suscriptor);
    void cinEstado(Suscriptor &suscriptor);
    void cinClave(Suscriptor &suscriptor);
    int generarIdSuscriptor();
    SuscriptoresArchivo& getArchivo();
    void exportarBackup();
    void importarBackup();

private:
    Consola _consola;
    Suscriptor _suscriptor;
    SuscriptoresArchivo _archivoSuscriptores;
    SuscriptoresArchivo _backupSuscriptores;
};
