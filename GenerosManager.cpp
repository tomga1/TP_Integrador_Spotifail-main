#include "GenerosManager.h"
#include <iostream>

GenerosManager::GenerosManager() {
    _backupGeneros.setRuta("registers/Generos.bkp");
}

void GenerosManager::mostrarMenu() {
    int opcion = 1;

    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("GENEROS");
        std::cout << "(1) AGREGAR GENERO\n";
        std::cout << "(2) EDITAR GENERO\n";
        std::cout << "(3) BUSCAR GENERO\n";
        std::cout << "(4) LISTAR GENEROS\n";
        _consola.imprimirLinea();
        std::cout << "(5) EXPORTAR BACKUP\n";
        std::cout << "(6) IMPORTAR BACKUP\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 6);

        switch (opcion) {
            case 1: agregarGenero(); break;
            case 2: editarGenero(); break;
            case 3: buscarGenero(); break;
            case 4: mostrarMenuListados(); break;
            case 5: exportarBackup(); break;
            case 6: importarBackup(); break;
        }

    } while (opcion != 0);
}

bool GenerosManager::agregarGenero() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("ALTA DE GENERO");

    _genero.setIdGenero(generarIdGenero());
    cinNombre(_genero);
    _genero.setInactivo(false);

    std::cout << "\nDesea guardar el registro? [S/N]: ";
    if (_consola.validarBool()) {
        if (_archivoGeneros.escribir(_genero)) {
            std::cout << "Registro guardado correctamente.\n";
        } else {
            std::cout << "Error al guardar el registro.\n";
        }
    } else {
        std::cout << "Registro descartado por el usuario.\n";
    }

    _consola.pausar();
    return true;
}

bool GenerosManager::editarGenero() {
    int resultado = buscarGenero();
    if (resultado == -1) return false;

    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("EDITAR GENERO");
        _consola.centrarYMostrar(_genero.getNombre());
        std::cout << "\n";
        std::cout << "(1) EDITAR NOMBRE\n";
        std::cout << "(2) CAMBIAR ESTADO (ACTIVO / INACTIVO)\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 2);

        switch (opcion) {
            case 1: cinNombre(_genero); break;
            case 2: cinEstado(_genero); break;
        }

    } while (opcion != 0);

    int indice = _archivoGeneros.buscarPorId(_genero.getIdGenero());
    return _archivoGeneros.sobrescribir(_genero, indice);
}

int GenerosManager::buscarGenero() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("BUSCAR GENERO");

    std::cout << "(1) POR ID\n";
    std::cout << "(2) POR NOMBRE\n";

    int opcion = _consola.validarInt(0, 2);
    switch (opcion) {
        case 1: {
            std::cout << "Ingrese ID: ";
            int id = _consola.validarInt(1);
            int indice = _archivoGeneros.buscarPorId(id);
            if (indice >= 0) {
                _genero = _archivoGeneros.leer(indice);
                mostrarGenero();
                _consola.pausar();
            }
            return indice;
        }
        case 2: {
            std::string nombre;
            std::cout << "Ingrese nombre: ";
            std::cin.ignore();
            getline(std::cin, nombre);

            int total = _archivoGeneros.contarRegistros();
            for (int i = 0; i < total; i++) {
                Genero reg = _archivoGeneros.leer(i);
                if (nombre == reg.getNombre()) {
                    _genero = reg;
                    mostrarGenero();
                    _consola.pausar();
                    return i;
                }
            }
            std::cout << "No se encontro el genero.\n";
            _consola.pausar();
            return -1;
        }
        default: return -1;
    }
}

void GenerosManager::mostrarMenuListados() {
    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("LISTAR GENEROS");
        std::cout << "(1) TODOS\n";
        std::cout << "(2) SOLO ACTIVOS\n";
        std::cout << "(3) SOLO INACTIVOS\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);
        switch (opcion) {
            case 1: listarGeneros(true, true); break;
            case 2: listarGeneros(true, false); break;
            case 3: listarGeneros(false, true); break;
        }
    } while (opcion != 0);
}

void GenerosManager::listarGeneros(bool activos, bool inactivos) {
    _consola.limpiar();
    int total = _archivoGeneros.contarRegistros();

    for (int i = 0; i < total; i++) {
        Genero reg = _archivoGeneros.leer(i);
        if ((reg.getInactivo() == false && activos) ||
            (reg.getInactivo() == true && inactivos)) {
            _genero = reg;
            mostrarGenero();
        }
    }
    _consola.pausar();
}

void GenerosManager::mostrarGenero() {
    _consola.mostrarEncabezadoMenu("DATOS DEL GENERO");
    std::cout << "ID: " << _genero.getIdGenero() << "\n";
    std::cout << "Nombre: " << _genero.getNombre() << "\n";
    _consola.imprimirBool(!_genero.getInactivo(), "Estado: Activo\n", "Estado: Inactivo\n");
}

void GenerosManager::cinNombre(Genero &g) {
    std::string nombre;
    std::cout << "Ingrese nombre: ";
    std::cin.ignore();
    getline(std::cin, nombre);
    g.setNombre(nombre);
}

void GenerosManager::cinEstado(Genero &g) {
    g.setInactivo(!g.getInactivo());
    std::cout << (g.getInactivo() ? "El genero fue dado de baja.\n" : "El genero fue reactivado.\n");
    _consola.pausar();
}

int GenerosManager::generarIdGenero() {
    int total = _archivoGeneros.contarRegistros();
    return total + 1;
}

void GenerosManager::exportarBackup() {
    int total = _archivoGeneros.contarRegistros();
    if (total == 0) {
        std::cout << "No hay registros para exportar.\n";
        _consola.pausar();
        return;
    }

    Genero *vec = new Genero[total];
    for (int i = 0; i < total; i++) {
        vec[i] = _archivoGeneros.leer(i);
        _backupGeneros.escribir(vec[i]);
    }
    delete[] vec;
    std::cout << "Backup exportado correctamente.\n";
    _consola.pausar();
}

void GenerosManager::importarBackup() {
    std::cout << "Desea reemplazar los registros actuales con el backup? [S/N]: ";
    if (!_consola.validarBool()) {
        std::cout << "Importacion cancelada.\n";
        return;
    }

    int total = _backupGeneros.contarRegistros();
    Genero *vec = new Genero[total];

    for (int i = 0; i < total; i++) vec[i] = _backupGeneros.leer(i);
    _archivoGeneros.crearArchivoVacio();

    for (int i = 0; i < total; i++) _archivoGeneros.escribir(vec[i]);
    delete[] vec;

    std::cout << "Backup importado correctamente.\n";
    _consola.pausar();
}
