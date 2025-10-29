#include "InterpretesManager.h"
#include <iostream>

InterpretesManager::InterpretesManager() {
    _backupInterpretes.setRuta("registers/Interpretes.bkp");
}

void InterpretesManager::mostrarMenu() {
    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("INTERPRETES");
        std::cout << "(1) AGREGAR INTERPRETE\n";
        std::cout << "(2) EDITAR INTERPRETE\n";
        std::cout << "(3) BUSCAR INTERPRETE\n";
        std::cout << "(4) LISTAR INTERPRETES\n";
        _consola.imprimirLinea();
        std::cout << "(5) EXPORTAR BACKUP\n";
        std::cout << "(6) IMPORTAR BACKUP\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 6);

        switch (opcion) {
            case 1: agregarInterprete(); break;
            case 2: editarInterprete(); break;
            case 3: buscarInterprete(); break;
            case 4: mostrarMenuListados(); break;
            case 5: exportarBackup(); break;
            case 6: importarBackup(); break;
        }

    } while (opcion != 0);
}

bool InterpretesManager::agregarInterprete() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("ALTA DE INTERPRETE");

    _interprete.setIdInterprete(generarIdInterprete());
    cinNombre(_interprete);
    cinGenero(_interprete);
    _interprete.setActivo(true);

    std::cout << "\nDesea guardar el registro? [S/N]: ";
    if (_consola.validarBool()) {
        if (_archivoInterpretes.escribir(_interprete)) {
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

bool InterpretesManager::editarInterprete() {
    int resultado = buscarInterprete();
    if (resultado == -1) return false;

    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("EDITAR INTERPRETE");
        _consola.centrarYMostrar(_interprete.getNombre());
        std::cout << "\n";
        std::cout << "(1) EDITAR NOMBRE\n";
        std::cout << "(2) CAMBIAR GENERO\n";
        std::cout << "(3) CAMBIAR ESTADO (ACTIVO / INACTIVO)\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);

        switch (opcion) {
            case 1: cinNombre(_interprete); break;
            case 2: cinGenero(_interprete); break;
            case 3: cinEstado(_interprete); break;
        }

    } while (opcion != 0);

    int indice = _archivoInterpretes.buscarPorId(_interprete.getIdInterprete());
    return _archivoInterpretes.sobrescribir(_interprete, indice);
}

int InterpretesManager::buscarInterprete() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("BUSCAR INTERPRETE");

    std::cout << "(1) POR ID\n";
    std::cout << "(2) POR NOMBRE\n";

    int opcion = _consola.validarInt(0, 2);
    switch (opcion) {
        case 1: {
            std::cout << "Ingrese ID: ";
            int id = _consola.validarInt(1);
            int indice = _archivoInterpretes.buscarPorId(id);
            if (indice >= 0) {
                _interprete = _archivoInterpretes.leer(indice);
                mostrarInterprete();
                _consola.pausar();
            }
            return indice;
        }
        case 2: {
            std::string nombre;
            std::cout << "Ingrese nombre: ";
            std::cin.ignore();
            getline(std::cin, nombre);

            int total = _archivoInterpretes.contarRegistros();
            for (int i = 0; i < total; i++) {
                Interprete reg = _archivoInterpretes.leer(i);
                if (nombre == reg.getNombre()) {
                    _interprete = reg;
                    mostrarInterprete();
                    _consola.pausar();
                    return i;
                }
            }
            std::cout << "No se encontro el interprete.\n";
            _consola.pausar();
            return -1;
        }
        default: return -1;
    }
}

void InterpretesManager::mostrarMenuListados() {
    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("LISTAR INTERPRETES");
        std::cout << "(1) TODOS\n";
        std::cout << "(2) SOLO ACTIVOS\n";
        std::cout << "(3) SOLO INACTIVOS\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);
        switch (opcion) {
            case 1: listarInterpretes(true, true); break;
            case 2: listarInterpretes(true, false); break;
            case 3: listarInterpretes(false, true); break;
        }
    } while (opcion != 0);
}

void InterpretesManager::listarInterpretes(bool activos, bool inactivos) {
    _consola.limpiar();
    int total = _archivoInterpretes.contarRegistros();

    for (int i = 0; i < total; i++) {
        Interprete reg = _archivoInterpretes.leer(i);
        if ((reg.getActivo() && activos) || (!reg.getActivo() && inactivos)) {
            _interprete = reg;
            mostrarInterprete();
        }
    }
    _consola.pausar();
}

void InterpretesManager::mostrarInterprete() {
    _consola.mostrarEncabezadoMenu("DATOS DEL INTERPRETE");
    Genero gen = _generosArchivo.leerPorId(_interprete.getIdGenero());
    std::cout << "ID: " << _interprete.getIdInterprete() << "\n";
    std::cout << "Nombre: " << _interprete.getNombre() << "\n";
    std::cout << "Genero: " << gen.getNombre() << "\n";
    _consola.imprimirBool(_interprete.getActivo(), "Estado: Activo\n", "Estado: Inactivo\n");
}


void InterpretesManager::cinNombre(Interprete &i) {
    std::string nombre;
    std::cout << "Ingrese nombre: ";
    std::cin.ignore();
    getline(std::cin, nombre);
    i.setNombre(nombre);
}

void InterpretesManager::cinGenero(Interprete &i) {
    int idGenero;
    std::cout << "Ingrese ID Genero: ";
    idGenero = _consola.validarInt(1);
    i.setIdGenero(idGenero);
}

void InterpretesManager::cinEstado(Interprete &i) {
    i.setActivo(!i.getActivo());
    std::cout << (i.getActivo() ? "El interprete fue activado.\n" : "El interprete fue dado de baja.\n");
    _consola.pausar();
}

int InterpretesManager::generarIdInterprete() {
    int total = _archivoInterpretes.contarRegistros();
    return total + 1;
}

void InterpretesManager::exportarBackup() {
    int total = _archivoInterpretes.contarRegistros();
    if (total == 0) {
        std::cout << "No hay registros para exportar.\n";
        _consola.pausar();
        return;
    }

    Interprete *vec = new Interprete[total];
    for (int i = 0; i < total; i++) {
        vec[i] = _archivoInterpretes.leer(i);
        _backupInterpretes.escribir(vec[i]);
    }
    delete[] vec;
    std::cout << "Backup exportado correctamente.\n";
    _consola.pausar();
}

void InterpretesManager::importarBackup() {
    std::cout << "Desea reemplazar los registros actuales con el backup? [S/N]: ";
    if (!_consola.validarBool()) {
        std::cout << "Importacion cancelada.\n";
        return;
    }

    int total = _backupInterpretes.contarRegistros();
    Interprete *vec = new Interprete[total];

    for (int i = 0; i < total; i++) vec[i] = _backupInterpretes.leer(i);
    _archivoInterpretes.crearArchivoVacio();

    for (int i = 0; i < total; i++) _archivoInterpretes.escribir(vec[i]);
    delete[] vec;

    std::cout << "Backup importado correctamente.\n";
    _consola.pausar();
}
