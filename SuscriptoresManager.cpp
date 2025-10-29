#include "SuscriptoresManager.h"

SuscriptoresManager::SuscriptoresManager() {
    _backupSuscriptores.setRuta("registers/suscriptores.bkp");
}

void SuscriptoresManager::mostrarMenu() {
    int opcion = 1;

    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("SUSCRIPTORES");
        std::cout << "(1) AGREGAR SUSCRIPTOR\n";
        std::cout << "(2) EDITAR SUSCRIPTOR\n";
        std::cout << "(3) BUSCAR SUSCRIPTOR\n";
        std::cout << "(4) LISTAR SUSCRIPTORES\n";
        _consola.imprimirLinea();
        std::cout << "(5) EXPORTAR BACKUP\n";
        std::cout << "(6) IMPORTAR BACKUP\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 6);

        switch (opcion) {
        case 1: agregarSuscriptor(); break;
        case 2: editarSuscriptor(); break;
        case 3: buscarSuscriptor(); break;
        case 4: mostrarMenuListados(); break;
        case 5: exportarBackup(); break;
        case 6: importarBackup(); break;
        }

    } while (opcion != 0);
}


bool SuscriptoresManager::agregarSuscriptor() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("ALTA DE SUSCRIPTOR");

    _suscriptor.setIdSuscriptor(generarIdSuscriptor());
    cinDni(_suscriptor);
    cinNombre(_suscriptor);
    cinApellido(_suscriptor);
    cinTelefono(_suscriptor);
    cinEmail(_suscriptor);
    cinFechaNacimiento(_suscriptor);
    cinClave(_suscriptor);
    _suscriptor.setInactivo(false);

    std::cout << "\nDesea guardar el registro? [S/N]: ";
    if (_consola.validarBool()) {
        if (_archivoSuscriptores.escribir(_suscriptor)) {
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


bool SuscriptoresManager::editarSuscriptor() {
    int resultado = buscarSuscriptor();
    if (resultado == -1) return false;

    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("EDITAR SUSCRIPTOR");
        _consola.centrarYMostrar(_suscriptor.getNombre());
        std::cout << "\n";
        std::cout << "(1) EDITAR NOMBRE\n";
        std::cout << "(2) EDITAR APELLIDO\n";
        std::cout << "(3) EDITAR DNI\n";
        std::cout << "(4) EDITAR TELÉFONO\n";
        std::cout << "(5) EDITAR EMAIL\n";
        std::cout << "(6) EDITAR FECHA DE NACIMIENTO\n";
        std::cout << "(7) CAMBIAR ESTADO (ACTIVO / INACTIVO)\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 7);

        switch (opcion) {
        case 1: cinNombre(_suscriptor); break;
        case 2: cinApellido(_suscriptor); break;
        case 3: cinDni(_suscriptor); break;
        case 4: cinTelefono(_suscriptor); break;
        case 5: cinEmail(_suscriptor); break;
        case 6: cinFechaNacimiento(_suscriptor); break;
        case 7: cinEstado(_suscriptor); break;
        }

    } while (opcion != 0);

    int indice = _archivoSuscriptores.buscarPorId(_suscriptor.getIdSuscriptor());
    return _archivoSuscriptores.sobrescribir(_suscriptor, indice);
}


int SuscriptoresManager::buscarSuscriptor() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("BUSCAR SUSCRIPTOR");

    std::cout << "(1) POR ID\n";
    std::cout << "(2) POR NOMBRE\n";
    std::cout << "(3) POR DNI\n";

    int opcion = _consola.validarInt(0, 3);
    switch (opcion) {
    case 1: return buscarPorId();
    case 2: return buscarPorNombre();
    case 3: return buscarPorDni();
    default: return -1;
    }
}

int SuscriptoresManager::buscarPorId() {
    std::cout << "Ingrese ID: ";
    int id = _consola.validarInt(1);
    int indice = _archivoSuscriptores.buscarPorId(id);
    if (indice >= 0) {
        _suscriptor = _archivoSuscriptores.leer(indice);
        mostrarSuscriptor();
        _consola.pausar();
    }
    return indice;
}

int SuscriptoresManager::buscarPorDni() {
    std::cout << "Ingrese DNI: ";
    int dni = _consola.validarInt(1);
    int indice = _archivoSuscriptores.buscarPorDni(dni);
    if (indice >= 0) {
        _suscriptor = _archivoSuscriptores.leer(indice);
        mostrarSuscriptor();
        _consola.pausar();
    }
    return indice;
}

int SuscriptoresManager::buscarPorNombre() {
    std::string nombre;
    std::cout << "Ingrese nombre: ";
    std::cin.ignore();
    getline(std::cin, nombre);

    int total = _archivoSuscriptores.contarRegistros();
    for (int i = 0; i < total; i++) {
        Suscriptor reg = _archivoSuscriptores.leer(i);
        if (nombre == reg.getNombre()) {
            _suscriptor = reg;
            mostrarSuscriptor();
            _consola.pausar();
            return i;
        }
    }
    std::cout << "No se encontró el suscriptor.\n";
    _consola.pausar();
    return -1;
}


void SuscriptoresManager::mostrarMenuListados() {
    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("LISTAR SUSCRIPTORES");
        std::cout << "(1) TODOS\n";
        std::cout << "(2) SOLO ACTIVOS\n";
        std::cout << "(3) SOLO INACTIVOS\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);
        switch (opcion) {
        case 1: listarSuscriptores(true, true); break;
        case 2: listarSuscriptores(true, false); break;
        case 3: listarSuscriptores(false, true); break;
        }
    } while (opcion != 0);
}

void SuscriptoresManager::listarSuscriptores(bool activos, bool inactivos) {
    _consola.limpiar();
    int total = _archivoSuscriptores.contarRegistros();

    for (int i = 0; i < total; i++) {
        Suscriptor reg = _archivoSuscriptores.leer(i);
        if ((reg.getInactivo() == false && activos) ||
            (reg.getInactivo() == true && inactivos)) {
            _suscriptor = reg;
            mostrarSuscriptor();
        }
    }
    _consola.pausar();
}

void SuscriptoresManager::mostrarSuscriptor() {
    _consola.mostrarEncabezadoMenu("DATOS DEL SUSCRIPTOR");
    std::cout << "ID: " << _suscriptor.getIdSuscriptor() << "\n";
    std::cout << "Nombre: " << _suscriptor.getNombre() << " " << _suscriptor.getApellido() << "\n";
    std::cout << "DNI: " << _suscriptor.getDni() << "\n";
    std::cout << "Telefono: " << _suscriptor.getTelefono() << "\n";
    std::cout << "Email: " << _suscriptor.getEmail() << "\n";
    std::cout << "Fecha Nacimiento: " << _suscriptor.getFechaNacimiento().toString() << "\n";
    _consola.imprimirBool(!_suscriptor.getInactivo(), "Estado: Activo\n", "Estado: Inactivo\n");
}


void SuscriptoresManager::cinNombre(Suscriptor &s) {
    std::string nombre;
    std::cout << "Ingrese nombre: ";
    std::cin.ignore();
    getline(std::cin, nombre);
    s.setNombre(nombre);
}

void SuscriptoresManager::cinApellido(Suscriptor &s) {
    std::string apellido;
    std::cout << "Ingrese apellido: ";
    getline(std::cin, apellido);
    s.setApellido(apellido);
}

void SuscriptoresManager::cinDni(Suscriptor &s) {
    std::cout << "Ingrese DNI: ";
    int dni = _consola.validarInt(1);
    s.setDni(dni);
}

void SuscriptoresManager::cinTelefono(Suscriptor &s) {
    std::string tel;
    std::cout << "Ingrese telefono: ";
    std::cin.ignore();
    getline(std::cin, tel);
    s.setTelefono(tel);
}

void SuscriptoresManager::cinClave(Suscriptor &s) {
    std::string cla;
    std::cout << "Ingrese clave: ";
    std::cin.ignore();
    getline(std::cin, cla);
    s.setClave(cla);
}

void SuscriptoresManager::cinEmail(Suscriptor &s) {
    std::string mail;
    std::cout << "Ingrese email: ";
    getline(std::cin, mail);
    s.setEmail(mail);
}

void SuscriptoresManager::cinFechaNacimiento(Suscriptor &s) {
    int d, m, a;
    std::cout << "Ingrese fecha de nacimiento (D M A): ";
    std::cin >> d >> m >> a;
    Fecha f(d, m, a);
    s.setFechaNacimiento(f);
}

void SuscriptoresManager::cinEstado(Suscriptor &s) {
    s.setInactivo(!s.getInactivo());
    std::cout << (s.getInactivo() ? "El suscriptor fue dado de baja.\n" : "El suscriptor fue reactivado.\n");
    _consola.pausar();
}


int SuscriptoresManager::generarIdSuscriptor() {
    int total = _archivoSuscriptores.contarRegistros();
    return total + 1;
}

SuscriptoresArchivo& SuscriptoresManager::getArchivo() {
    return _archivoSuscriptores;
}


void SuscriptoresManager::exportarBackup() {
    int total = _archivoSuscriptores.contarRegistros();
    if (total == 0) {
        std::cout << "No hay registros para exportar.\n";
        _consola.pausar();
        return;
    }

    Suscriptor *vec = new Suscriptor[total];
    for (int i = 0; i < total; i++) {
        vec[i] = _archivoSuscriptores.leer(i);
        _backupSuscriptores.escribir(vec[i]);
    }
    delete[] vec;
    std::cout << "Backup exportado correctamente.\n";
    _consola.pausar();
}

void SuscriptoresManager::importarBackup() {
    std::cout << "Desea reemplazar los registros actuales con el backup? [S/N]: ";
    if (!_consola.validarBool()) {
        std::cout << "Importación cancelada.\n";
        return;
    }

    int total = _backupSuscriptores.contarRegistros();
    Suscriptor *vec = new Suscriptor[total];

    for (int i = 0; i < total; i++) vec[i] = _backupSuscriptores.leer(i);
    _archivoSuscriptores.crearArchivoVacio();

    for (int i = 0; i < total; i++) _archivoSuscriptores.escribir(vec[i]);
    delete[] vec;

    std::cout << "Backup importado correctamente.\n";
    _consola.pausar();
}
