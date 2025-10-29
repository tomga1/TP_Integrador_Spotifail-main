#include "AlbumsManager.h"

AlbumsManager::AlbumsManager() {
    _backupAlbums.setRuta("registers/Albums.bkp");
}

void AlbumsManager::mostrarMenu() {
    int opcion = 1;

    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("ALBUMS");
        std::cout << "(1) AGREGAR ALBUM\n";
        std::cout << "(2) AGREGAR CANCION A ALBUM\n";
        std::cout << "(3) EDITAR ALBUM\n";
        std::cout << "(4) BUSCAR ALBUM\n";
        std::cout << "(5) LISTAR ALBUM\n";
        _consola.imprimirLinea();
        std::cout << "(6) EXPORTAR BACKUP\n";
        std::cout << "(7) IMPORTAR BACKUP\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 7);

        switch (opcion) {
        case 1: agregarAlbum(); break;
        case 2: agregarCancionAAlbum(); break;
        case 3: editarAlbum(); break;
        case 4: buscarAlbum(); break;
        case 5: mostrarMenuListados(); break;
        case 6: exportarBackup(); break;
        case 7: importarBackup(); break;
        }

    } while (opcion != 0);
}


bool AlbumsManager::agregarAlbum() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("ALTA DE ALBUM");

    _album.setIdAlbum(generarIdAlbum());
    cinNombre(_album);
    _album.setInactivo(false);

    std::cout << "\nDesea guardar el registro? [S/N]: ";
    if (_consola.validarBool()) {
        if (_archivoAlbums.escribir(_album)) {
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



void AlbumsManager::agregarCancionAAlbum() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("AGREGAR CANCION A ALBUM");

    int idAlbum=0, idCancion=0;
    std::cout << "Ingrese ID del album: ";
    std::cin >> idAlbum;

    std::cout << "Ingrese ID de la cancion: ";
    std::cin >> idCancion;

    int indiceCancion = _cancionArchivo.buscarPorId(idCancion);
    if (indiceCancion == -1) {
        std::cout << "Cancion no encontrada.\n";
        _consola.pausar();
        return;
    }

    Album album = _archivoAlbums.leerPorId(idAlbum);
    if (album.getIdAlbum() == 0) {
        std::cout << "Album no encontrado o inactivo.\n";
        _consola.pausar();
        return;
    }

    Cancion cancion = _cancionArchivo.leer(indiceCancion);
    if (cancion.getIdCancion() == 0) {
        std::cout << "Cancion no encontrada o inactiva.\n";
        _consola.pausar();
        return;
    }

    cancion.setIdAlbum(idAlbum);

    if (_cancionArchivo.sobreEscribirPorId(cancion, indiceCancion)) {
        std::cout << "La cancion '"<<cancion.getTitulo()<<"' fue agregada exitosamente al album '"
                  << album.getNombre() << "'.\n";
    } else {
        std::cout << "Error al intentar actualizar la cancion.\n";
    }

    _consola.pausar();
}






void AlbumsManager::listarCancionesDelAlbum(int idAlbum) {
    int total = _cancionArchivo.getCantidadRegistros();
    for (int i = 0; i < total; i++) {
        Cancion reg = _cancionArchivo.leer(i);
        if (reg.getIdAlbum() == idAlbum) {
            std::cout << "- " << reg.getTitulo() << " (" << reg.getAutor() << ")\n";
        }
    }
}


bool AlbumsManager::editarAlbum() {
    int resultado = buscarAlbum();
    if (resultado == -1) return false;

    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("EDITAR ALBUM");
        _consola.centrarYMostrar(_album.getNombre());
        std::cout << "\n";
        std::cout << "(1) EDITAR NOMBRE\n";
        std::cout << "(2) CAMBIAR ESTADO (ACTIVO / INACTIVO)\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 2);

        switch (opcion) {
        case 1: cinNombre(_album); break;
        case 2: cinEstado(_album); break;
        }

    } while (opcion != 0);

    int indice = _archivoAlbums.buscarPorId(_album.getIdAlbum());
    return _archivoAlbums.sobrescribir(_album, indice);
}


int AlbumsManager::buscarAlbum() {
    _consola.limpiar();
    _consola.mostrarEncabezadoMenu("BUSCAR ALBUM");

    std::cout << "(1) POR ID\n";
    std::cout << "(2) POR NOMBRE\n";

    int opcion = _consola.validarInt(0, 2);
    switch (opcion) {
    case 1: return buscarPorId();
    case 2: return buscarPorNombre();
    default: return -1;
    }
}

int AlbumsManager::buscarPorId() {
    std::cout << "Ingrese ID: ";
    int id = _consola.validarInt(1);
    int indice = _archivoAlbums.buscarPorId(id);
    if (indice >= 0) {
        _album = _archivoAlbums.leer(indice);
        mostrarAlbum();
        _consola.pausar();
    }
    return indice;
}

int AlbumsManager::buscarPorNombre() {
    std::string nombre;
    std::cout << "Ingrese nombre: ";
    std::cin.ignore();
    getline(std::cin, nombre);

    int total = _archivoAlbums.contarRegistros();
    for (int i = 0; i < total; i++) {
        Album reg = _archivoAlbums.leer(i);
        if (nombre == reg.getNombre()) {
            _album = reg;
            mostrarAlbum();
            _consola.pausar();
            return i;
        }
    }
    std::cout << "No se encontro el suscriptor.\n";
    _consola.pausar();
    return -1;
}


void AlbumsManager::mostrarMenuListados() {
    int opcion = 1;
    do {
        _consola.limpiar();
        _consola.mostrarEncabezadoMenu("LISTAR ALBUMS");
        std::cout << "(1) TODOS\n";
        std::cout << "(2) SOLO ACTIVOS\n";
        std::cout << "(3) SOLO INACTIVOS\n";
        _consola.mostrarPieMenu();

        opcion = _consola.validarInt(0, 3);
        switch (opcion) {
        case 1: listarAlbums(true, true, _cancionesManager); break;
        case 2: listarAlbums(true, false, _cancionesManager); break;
        case 3: listarAlbums(false, true, _cancionesManager); break;
        }
    } while (opcion != 0);
}

void AlbumsManager::listarAlbums(bool activos, bool inactivos, CancionesManager& cancionesManager) {
    _consola.limpiar();
    int total = _archivoAlbums.contarRegistros();

    for (int i = 0; i < total; i++) {
        Album reg = _archivoAlbums.leer(i);
        if ((reg.getInactivo() == false && activos) ||
            (reg.getInactivo() == true && inactivos)) {

            _album = reg;
            mostrarAlbum();

            cancionesManager.listarCancionesPorAlbum(reg.getIdAlbum());
        }
    }

    _consola.pausar();
}

void AlbumsManager::mostrarAlbum() {
    _consola.mostrarEncabezadoMenu("DATOS DEL ALBUM");
    std::cout << "ID: " << _album.getIdAlbum() << "\n";
    std::cout << "Nombre: " << _album.getNombre() << "\n";
    _consola.imprimirBool(!_album.getInactivo(), "Estado: Activo\n", "Estado: Inactivo\n");
}


void AlbumsManager::cinNombre(Album &a) {
    std::string nombre;
    std::cout << "Ingrese nombre: ";
    std::cin.ignore();
    getline(std::cin, nombre);
    a.setNombre(nombre);
}

void AlbumsManager::cinEstado(Album &a) {
    a.setInactivo(!a.getInactivo());
    std::cout << (a.getInactivo() ? "El album fue dado de baja.\n" : "El album fue reactivado.\n");
    _consola.pausar();
}


int AlbumsManager::generarIdAlbum() {
    int total = _archivoAlbums.contarRegistros();
    return total + 1;
}


void AlbumsManager::exportarBackup() {
    int total = _archivoAlbums.contarRegistros();
    if (total == 0) {
        std::cout << "No hay registros para exportar.\n";
        _consola.pausar();
        return;
    }

    Album *vec = new Album[total];
    for (int i = 0; i < total; i++) {
        vec[i] = _archivoAlbums.leer(i);
        _backupAlbums.escribir(vec[i]);
    }
    delete[] vec;
    std::cout << "Backup exportado correctamente.\n";
    _consola.pausar();
}

void AlbumsManager::importarBackup() {
    std::cout << "Desea reemplazar los registros actuales con el backup? [S/N]: ";
    if (!_consola.validarBool()) {
        std::cout << "Importacion cancelada.\n";
        return;
    }

    int total = _backupAlbums.contarRegistros();
    Album *vec = new Album[total];

    for (int i = 0; i < total; i++) vec[i] = _backupAlbums.leer(i);
    _archivoAlbums.crearArchivoVacio();

    for (int i = 0; i < total; i++) _archivoAlbums.escribir(vec[i]);
    delete[] vec;

    std::cout << "Backup importado correctamente.\n";
    _consola.pausar();
}
