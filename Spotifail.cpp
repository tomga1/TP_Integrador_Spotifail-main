#include <iostream>
#include "Spotifail.h"

void Spotifail::run() {


    int idUsuario = -1;
    while (idUsuario == -1) {
        idUsuario = login();
    }


    int seleccion = 1;

    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("lml Spotifail lml");
        std::cout << "(1) SUSCRIPTORES\n";
        std::cout << "(2) CANCIONES\n";
        std::cout << "(3) PLAYLISTS\n";
        std::cout << "(4) ALBUMES\n";
        std::cout << "(5) UTILIDADES\n";
        _consola.imprimirLinea();
        std::cout << "(6) ACERCA DE SPOTIFAIL\n";
        std::cout << "(0) SALIR\n";

        seleccion = _consola.validarInt(0, 6);

        switch (seleccion) {
            case 1:
                    _suscriptoresManager.mostrarMenu();
                break;
            case 2:
                    _cancionManager.mostrarMenu();

                break;
            case 3:
                    _consola.limpiar();
                    std::cout << "MODULO EN DESARROLLO.\n";
                    _consola.pausar();
                break;
            case 4:
                    _albumManager.mostrarMenu();
                break;

            case 5:
                    menuUtilidades();

                break;

            case 6:
                about();
                break;
        }

    } while (seleccion != 0);
}

void Spotifail::menuUtilidades() {
    int opcion;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("UTILIDADES");
        std::cout << "(1) GENEROS\n";
        std::cout << "(2) INTERPRETES\n";
        std::cout << "(3) ACCESOS\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);

        switch (opcion) {
            case 1: _generosManager.mostrarMenu();
             break;
            case 2: _interpreteManager.mostrarMenu();
             break;
            case 3: _accesosManager.mostrarMenu();
             break;
        }
    } while (opcion != 0);
}

int Spotifail::login() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("LOGIN");

    int idUsuario;
    std::string claveIngresada;

    std::cout << "Ingrese ID de usuario: ";
    std::cin >> idUsuario;
    std::cin.ignore();

    std::cout << "Ingrese clave: ";
    getline(std::cin, claveIngresada);

    Suscriptor usuario = _suscriptoresManager.getArchivo().leerPorId(idUsuario);

    if (usuario.getIdSuscriptor() == 0) {
        std::cout << "Usuario no encontrado.\n";
        _consola.pausar();
        return -1;
    }

    if (usuario.getClave() != claveIngresada) {
        std::cout << "Clave incorrecta.\n";
        _consola.pausar();
        return -1;
    }

    std::cout << "Bienvenido, " << usuario.getNombre() << "!\n";

    _accesosManager.registrarAcceso(idUsuario);

    _consola.pausar();
    return idUsuario;
}


void Spotifail::about() {
    _consola.limpiar();
    std::cout << "SPOTIFAIL ES UN PROYECTO DE PROGRAMACION II.\n";
    std::cout << "© 2025 Spotifail Music Systems\n";
    _consola.pausar();
    _consola.limpiar();
}
