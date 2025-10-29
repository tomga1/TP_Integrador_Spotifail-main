#include "AlbumsArchivo.h"

AlbumsArchivo::AlbumsArchivo()
    : _ruta("registers/albums.dat") {}

AlbumsArchivo::AlbumsArchivo(const std::string &ruta)
    : _ruta(ruta) {}

void AlbumsArchivo::setRuta(const std::string &ruta) {
    _ruta = ruta;
}

std::string AlbumsArchivo::getRuta() const {
    return _ruta;
}


bool AlbumsArchivo::escribir(Album &reg) {
    FILE *pArchivo = fopen(getRuta().c_str(), "ab");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura.\n";
        return false;
    }

    bool ok = fwrite(&reg, sizeof(Album), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}


bool AlbumsArchivo::sobrescribir(Album &reg, int indice) {
    FILE *pArchivo = fopen(getRuta().c_str(), "rb+");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo abrir el archivo para sobrescritura.\n";
        return false;
    }

    fseek(pArchivo, sizeof(Album) * indice, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Album), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}


Album AlbumsArchivo::leer(int indice) {
    Album reg;
    FILE *pArchivo = fopen(getRuta().c_str(), "rb");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo abrir el archivo para lectura.\n";
        return reg;
    }

    fseek(pArchivo, sizeof(Album) * indice, SEEK_SET);
    fread(&reg, sizeof(Album), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

Album AlbumsArchivo::leerPorId(int idAlbum) {
    Album reg;
    int pos = buscarPorId(idAlbum);
    if (pos == -1) {
        reg.setIdAlbum(0);
        return reg;
    }
    return leer(pos);
}


int AlbumsArchivo::buscarPorId(int idAlbum) {
    int i = 0;
    int total = contarRegistros();
    while (i < total) {
        Album reg = leer(i);
        if (reg.getIdAlbum() == idAlbum) return i;
        i++;
    }
    return -1;
}


int AlbumsArchivo::buscarPorNombre(const std::string & nombre) {
    int i = 0;
    int total = contarRegistros();
    while (i < total) {
        Album reg = leer(i);
        if (reg.getNombre() == nombre) return i;
        i++;
    }
    return -1;
}


int AlbumsArchivo::contarRegistros() {
    FILE *pArchivo = fopen(getRuta().c_str(), "rb");
    if (pArchivo == NULL) return 0;

    fseek(pArchivo, 0, SEEK_END);
    int bytes = ftell(pArchivo);
    fclose(pArchivo);

    return bytes / sizeof(Album);
}


void AlbumsArchivo::crearArchivoVacio() {
    FILE *pArchivo = fopen(getRuta().c_str(), "wb");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo crear el archivo.\n";
        return;
    }
    fclose(pArchivo);
}
