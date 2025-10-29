#include "CancionesManager.h"

CancionesManager::CancionesManager() {
    _backupCanciones.setPath("registers/canciones.bkp");
}

void CancionesManager::mostrarMenu() {
    int opcion = 1;

    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("CANCIONES");
        std::cout << "(1) AGREGAR CANCION\n";
        std::cout << "(2) EDITAR CANCION\n";
        std::cout << "(3) BUSCAR CANCION\n";
        std::cout << "(4) LISTAR CANCIONES\n";
        _consola.imprimirLinea();
        std::cout << "(5) EXPORTAR BACKUP\n";
        std::cout << "(6) IMPORTAR BACKUP\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 6);

        switch (opcion) {
        case 1:
             agregarCancion();
            break;
        case 2:
             editarCancion();
            break;
        case 3:
             buscarCancion();
            break;
        case 4:
             mostrarMenuListados();
            break;
        case 5:
             exportarBackup();
            break;
        case 6:
             importarBackup();
            break;
        }

    } while (opcion != 0);
}

bool CancionesManager::agregarCancion() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("ALTA DE CANCION");

    _cancion.setIdCancion(generarIdCancion());
    cinTitulo(_cancion);
    cinAutor(_cancion);
    cinIdInterprete(_cancion);
    cinIdGenero(_cancion);
    cinFechaPublicacion(_cancion);
    _cancion.setInactivo(false);

    std::cout << "\nDesea guardar el registro? [S/N]: ";
    if (_consola.validarBool()) {
        if (_archivoCanciones.escribir(_cancion)) {
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

bool CancionesManager::editarCancion() {
    int resultado = buscarCancion();
    if (resultado == -1) return false;

    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("EDITAR CANCION");
        _consola.centrarYMostrar(_cancion.getTitulo());
        std::cout << "\n";
        std::cout << "(1) EDITAR TITULO\n";
        std::cout << "(2) EDITAR AUTOR\n";
        std::cout << "(3) EDITAR ID INTERPRETE\n";
        std::cout << "(4) EDITAR ID GENERO\n";
        std::cout << "(5) EDITAR FECHA PUBLICACION\n";
        std::cout << "(6) CAMBIAR ESTADO (ACTIVA / INACTIVA)\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 6);

        switch (opcion) {
        case 1: cinTitulo(_cancion); break;
        case 2: cinAutor(_cancion); break;
        case 3: cinIdInterprete(_cancion); break;
        case 4: cinIdGenero(_cancion); break;
        case 5: cinFechaPublicacion(_cancion); break;
        case 6: cinEstado(_cancion); break;
        }

    } while (opcion != 0);

    int indice = _archivoCanciones.buscarPorId(_cancion.getIdCancion());
    return _archivoCanciones.sobreEscribir(_cancion, indice);
}

int CancionesManager::buscarCancion() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("BUSCAR CANCION");

    std::cout << "(1) POR ID\n";
    std::cout << "(2) POR TITULO\n";
    std::cout << "(3) POR AUTOR\n";

    int opcion = _consola.validarInt(0, 3);
    switch (opcion) {
    case 1: return buscarPorId();
    case 2: return buscarPorTitulo();
    case 3: return buscarPorAutor();
    default: return -1;
    }
}

int CancionesManager::buscarPorId() {
    std::cout << "Ingrese ID: ";
    int id = _consola.validarInt(1);
    int indice = _archivoCanciones.buscarPorId(id);
    if (indice >= 0) {
        _cancion = _archivoCanciones.leer(indice);
        mostrarCancion();
        _consola.pausar();
    }
    return indice;
}

int CancionesManager::buscarPorTitulo() {
    std::string titulo;
    std::cout << "Ingrese titulo: ";
    std::cin.ignore();
    getline(std::cin, titulo);

    int total = _archivoCanciones.getCantidadRegistros();
    for (int i = 0; i < total; i++) {
        Cancion reg = _archivoCanciones.leer(i);
        if (titulo == reg.getTitulo()) {
            _cancion = reg;
            mostrarCancion();
            _consola.pausar();
            return i;
        }
    }
    std::cout << "No se encontro la cancion.\n";
    _consola.pausar();
    return -1;
}

int CancionesManager::buscarPorAutor() {
    std::string autor;
    std::cout << "Ingrese autor: ";
    std::cin.ignore();
    getline(std::cin, autor);

    int total = _archivoCanciones.getCantidadRegistros();
    for (int i = 0; i < total; i++) {
        Cancion reg = _archivoCanciones.leer(i);
        if (autor == reg.getAutor()) {
            _cancion = reg;
            mostrarCancion();
            _consola.pausar();
            return i;
        }
    }
    std::cout << "No se encontro el autor.\n";
    _consola.pausar();
    return -1;
}

void CancionesManager::mostrarMenuListados() {
    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("LISTAR CANCIONES");
        std::cout << "(1) TODAS\n";
        std::cout << "(2) SOLO ACTIVAS\n";
        std::cout << "(3) SOLO INACTIVAS\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);
        switch (opcion) {
        case 1: listarCanciones(true, true); break;
        case 2: listarCanciones(true, false); break;
        case 3: listarCanciones(false, true); break;
        }
    } while (opcion != 0);
}

void CancionesManager::listarCanciones(bool activas, bool inactivas) {
    _consola.limpiar();
    int total = _archivoCanciones.getCantidadRegistros();

    for (int i = 0; i < total; i++) {
        Cancion reg = _archivoCanciones.leer(i);
        if ((reg.getInactivo() == false && activas) ||
            (reg.getInactivo() == true && inactivas)) {
            _cancion = reg;
            mostrarCancion();
        }
    }
    _consola.pausar();
}

void CancionesManager::listarCancionesPorAlbum(int idAlbum) {
    int total = _archivoCanciones.getCantidadRegistros();
    for (int i = 0; i < total; i++) {
        Cancion c = _archivoCanciones.leer(i);
        if (c.getIdAlbum() == idAlbum) {
            std::cout << "   - " << c.getTitulo() << "\n";
        }
    }
}

void CancionesManager::mostrarCancion() {
    _consola.mostrarEncabezadoMenu("DATOS DE LA CANCION");
    Genero gen = _generosArchivo.leerPorId(_cancion.getIdGenero());
    Interprete intp = _interpretesArchivo.leerPorId(_cancion.getIdInterprete());
    std::cout << "ID: " << _cancion.getIdCancion() << "\n";
    std::cout << "Titulo: " << _cancion.getTitulo() << "\n";
    std::cout << "Autor: " << _cancion.getAutor() << "\n";
    std::cout << "Genero: " << gen.getNombre() << "\n";
    std::cout << "Interprete: " << intp.getNombre() << "\n";
    _album = _albumArchivos.leerPorId(_cancion.getIdAlbum());
    std::cout << "Album: " << _album.getNombre() << "\n";
    std::cout << "Fecha Publicacion: " << _cancion.getFechaPublicacion().toString() << "\n";
    _consola.imprimirBool(!_cancion.getInactivo(), "Estado: Activa\n", "Estado: Inactiva\n");
}

void CancionesManager::cinTitulo(Cancion &c) {
    std::string titulo;
    std::cout << "Ingrese titulo: ";
    std::cin.ignore();
    getline(std::cin, titulo);
    c.setTitulo(titulo);
}

void CancionesManager::cinAutor(Cancion &c) {
    std::string autor;
    std::cout << "Ingrese autor: ";
    getline(std::cin, autor);
    c.setAutor(autor);
}

void CancionesManager::cinIdInterprete(Cancion &c) {
    std::cout << "Ingrese ID del interprete: ";
    int id = _consola.validarInt(1);
    c.setIdInterprete(id);
}

void CancionesManager::cinIdAlbum(Cancion &c) {
    std::cout << "Ingrese ID del Album: ";
    int id = _consola.validarInt(1);
    c.setIdAlbum(id);
}

void CancionesManager::cinIdGenero(Cancion &c) {
    std::cout << "Ingrese ID del genero: ";
    int id = _consola.validarInt(1);
    c.setIdGenero(id);
}

void CancionesManager::cinFechaPublicacion(Cancion &c) {
    int d, m, a;
    std::cout << "Ingrese fecha de publicacion (D M A): ";
    std::cin >> d >> m >> a;
    Fecha f(d, m, a);
    c.setFechaPublicacion(f);
}

void CancionesManager::cinEstado(Cancion &c) {
    c.setInactivo(!c.getInactivo());
    std::cout << (c.getInactivo() ? "La cancion fue desactivada.\n" : "La cancion fue activada.\n");
    _consola.pausar();
}


int CancionesManager::generarIdCancion() {
    int total = _archivoCanciones.getCantidadRegistros();
    return total + 1;
}

void CancionesManager::exportarBackup() {
    int total = _archivoCanciones.getCantidadRegistros();
    if (total == 0) {
        std::cout << "No hay registros para exportar.\n";
        _consola.pausar();
        return;
    }

    Cancion *vec = new Cancion[total];
    for (int i = 0; i < total; i++) {
        vec[i] = _archivoCanciones.leer(i);
        _backupCanciones.escribir(vec[i]);
    }
    delete[] vec;
    std::cout << "Backup exportado correctamente.\n";
    _consola.pausar();
}

void CancionesManager::importarBackup() {
    std::cout << "Desea reemplazar los registros actuales con el backup? [S/N]: ";
    if (!_consola.validarBool()) {
        std::cout << "Importacion cancelada.\n";
        return;
    }

    int total = _backupCanciones.getCantidadRegistros();
    Cancion *vec = new Cancion[total];

    for (int i = 0; i < total; i++) vec[i] = _backupCanciones.leer(i);
    _archivoCanciones.crearArchivoVacio();

    for (int i = 0; i < total; i++) _archivoCanciones.escribir(vec[i]);
    delete[] vec;

    std::cout << "Backup importado correctamente.\n";
    _consola.pausar();
}
