#include "AccesosManager.h"
#include <iostream>
#include "FechaTiempo.h"

AccesosManager::AccesosManager() {
    _backupAccesos.setPath("registers/Accesos.bkp");
}

void AccesosManager::mostrarMenu() {
    int opcion = 1;

    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("ACCESOS");
        std::cout << "(1) LISTAR ACCESOS\n";
        _consola.imprimirLinea();
        std::cout << "(2) EXPORTAR BACKUP\n";
        std::cout << "(3) IMPORTAR BACKUP\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);

        switch (opcion) {
        case 1: listarTodosLosAccesos(suscriptoresManager); break;
        case 2: exportarBackup(); break;
        case 3: importarBackup(); break;
        }

    } while (opcion != 0);
}

void AccesosManager::registrarAcceso(int idSuscriptor) {
    Acceso a;

    int nuevoId = _archivoAccesos.contarRegistros() + 1;
    a.setIdAcceso(nuevoId);
    a.setIdSuscriptor(idSuscriptor);

    std::time_t t = std::time(nullptr);
    std::tm ahoraStruct = *std::localtime(&t);

    Fecha f(ahoraStruct.tm_mday, ahoraStruct.tm_mon + 1, ahoraStruct.tm_year + 1900);
    Tiempo ti(ahoraStruct.tm_hour, ahoraStruct.tm_min, ahoraStruct.tm_sec);

    FechaTiempo ft(f, ti);
    a.setFechaHora(ft);

    a.setInactivo(false);

    if (_archivoAccesos.escribir(a)) {
        std::cout << "Login exitoso. \n";
    } else {
        std::cout << "Error al registrar el acceso.\n";
    }
}


void AccesosManager::listarTodosLosAccesos(SuscriptoresManager& suscriptoresManager) {

    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("ACCESOS SUSCRIPTORES");

    int total = _archivoAccesos.contarRegistros();
    if (total == 0) {
        std::cout << "No hay accesos registrados.\n";
        return;
    }

    for (int i = 0; i < total; i++) {
        Acceso a = _archivoAccesos.leer(i);
        Suscriptor s = suscriptoresManager.getArchivo().leerPorId(a.getIdSuscriptor());
        std::cout << " ID de Acceso: " << a.getIdAcceso()<<"\n"
                  << " ID de Usuario: " << s.getIdSuscriptor()<<"\n"
                  << " Nombre de Usuario: " << s.getNombre()<<"\n"
                  << " Timestamp: " << a.getFechaHora().toString() << "\n";
                  _consola.imprimirLinea();
    }
    _consola.pausar();
}

void AccesosManager::exportarBackup() {
    int total = _archivoAccesos.contarRegistros();
    if (total == 0) {
        std::cout << "No hay registros para exportar.\n";
        _consola.pausar();
        return;
    }

    Acceso *vec = new Acceso[total];
    for (int i = 0; i < total; i++) {
        vec[i] = _archivoAccesos.leer(i);
        _backupAccesos.escribir(vec[i]);
    }
    delete[] vec;
    std::cout << "Backup exportado correctamente.\n";
    _consola.pausar();
}

void AccesosManager::importarBackup() {
    std::cout << "Desea reemplazar los registros actuales con el backup? [S/N]: ";
    if (!_consola.validarBool()) {
        std::cout << "Importacion cancelada.\n";
        return;
    }

    int total = _backupAccesos.contarRegistros();
    Acceso *vec = new Acceso[total];

    for (int i = 0; i < total; i++) vec[i] = _backupAccesos.leer(i);
    _archivoAccesos.crearArchivoVacio();

    for (int i = 0; i < total; i++) _archivoAccesos.escribir(vec[i]);
    delete[] vec;

    std::cout << "Backup importado correctamente.\n";
    _consola.pausar();
}
