#include <iostream>
#include <map>
#include "InformesManager.h"

using namespace std;

InformesManager::InformesManager() {
   /* _backupInformes.setPath("registers/informes.bkp");*/
}

void InformesManager::mostrarMenu() {
    int opcion = 1;

    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("INFORMES");
        std::cout << "(1) CANTIDAD TOTAL DE ACCESOS POR SUSCRIPTOR\n";
        std::cout << "(2) CANTIDAD TOTAL USUARIOS INACTIVOS\n";

        _consola.imprimirLinea();
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);

        switch (opcion) {
        case 1:
            informeCantidadAccesosPorSuscriptor();
            break;
        case 2:
            informeUsuariosInactivos();
            break;
        }

    } while (opcion != 0);
}


void InformesManager::informeCantidadAccesosPorSuscriptor() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("CANTIDAD TOTAL DE ACCESOS POR SUSCRIPTOR");

    int totalAccesos = _archivoAcceso.contarRegistros();
    if (totalAccesos == 0) {
        std::cout << "No hay accesos registrados.\n";
        _consola.pausar();
        return;
    }

    std::map<int, int> accesosPorSuscriptor;

    for (int i = 0; i < totalAccesos; i++) {
        Acceso acc = _archivoAcceso.leer(i);
        accesosPorSuscriptor[acc.getIdSuscriptor()]++;
    }

    for (auto &item : accesosPorSuscriptor) {
        int id = item.first;
        int cantidad = item.second;
        Suscriptor s = _archivoSuscriptores.leerPorId(id);
        std::cout << "Suscriptor: " << s.getNombre() << " - Accesos: " << cantidad << "\n";
    }

    _consola.pausar();
}

void InformesManager::informeUsuariosInactivos() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("Informe: Suscriptores Inactivos");

    int cantidad = _archivoSuscriptores.contarRegistros();
    bool hayInactivos = false;  // bandera

    for (int i = 0; i < cantidad; i++) {
        Suscriptor s = _archivoSuscriptores.leer(i);

        if (s.getInactivo()) {
            std::cout << "ID: " << s.getIdSuscriptor()
                      << " | Nombre: " << s.getNombre()
                      << " | Apellido: " << s.getApellido()
                      << std::endl;
            hayInactivos = true;
        }
    }

    if (!hayInactivos) {
        std::cout << "No existen suscriptores inactivos.\n";
    }

    _consola.pausar();
}




/*
void InformesManager::exportarBackup() {
 cout << "Exportando backup de informes..." << endl;
}

void InformesManager::importarBackup() {
    cout << "Importando backup de informes..." << endl;
}*/
