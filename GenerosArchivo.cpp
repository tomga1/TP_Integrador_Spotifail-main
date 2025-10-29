#include "GenerosArchivo.h"

GenerosArchivo::GenerosArchivo()
    : _ruta("registers/generos.dat") {}

GenerosArchivo::GenerosArchivo(const std::string &ruta)
    : _ruta(ruta) {}

void GenerosArchivo::setRuta(const std::string &ruta) {
    _ruta = ruta;
}

std::string GenerosArchivo::getRuta() const {
    return _ruta;
}

bool GenerosArchivo::escribir(Genero &reg) {
    FILE *pArchivo = fopen(_ruta.c_str(), "ab");
    if (!pArchivo) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura.\n";
        return false;
    }
    bool ok = fwrite(&reg, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool GenerosArchivo::sobrescribir(Genero &reg, int indice) {
    FILE *pArchivo = fopen(_ruta.c_str(), "rb+");
    if (!pArchivo) {
        std::cerr << "Error: no se pudo abrir el archivo para sobrescritura.\n";
        return false;
    }
    fseek(pArchivo, sizeof(Genero) * indice, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

Genero GenerosArchivo::leer(int indice) {
    Genero reg;
    FILE *pArchivo = fopen(_ruta.c_str(), "rb");
    if (!pArchivo) {
        std::cerr << "Error: no se pudo abrir el archivo para lectura.\n";
        return reg;
    }
    fseek(pArchivo, sizeof(Genero) * indice, SEEK_SET);
    fread(&reg, sizeof(Genero), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

Genero GenerosArchivo::leerPorId(int idGenero) {
    int total = contarRegistros();
    for (int i = 0; i < total; i++) {
        Genero reg = leer(i);
        if (reg.getIdGenero() == idGenero) return reg;
    }
    return Genero();
}


int GenerosArchivo::buscarPorId(int idGenero) {
    int total = contarRegistros();
    for (int i = 0; i < total; i++) {
        Genero reg = leer(i);
        if (reg.getIdGenero() == idGenero) return i;
    }
    return -1;
}

int GenerosArchivo::buscarPorNombre(const std::string &nombre) {
    int total = contarRegistros();
    for (int i = 0; i < total; i++) {
        Genero reg = leer(i);
        if (nombre == reg.getNombre()) return i;
    }
    return -1;
}

int GenerosArchivo::contarRegistros() {
    FILE *pArchivo = fopen(_ruta.c_str(), "rb");
    if (!pArchivo) return 0;
    fseek(pArchivo, 0, SEEK_END);
    int bytes = ftell(pArchivo);
    fclose(pArchivo);
    return bytes / sizeof(Genero);
}

void GenerosArchivo::crearArchivoVacio() {
    FILE *pArchivo = fopen(_ruta.c_str(), "wb");
    if (!pArchivo) {
        std::cerr << "Error: no se pudo crear el archivo.\n";
        return;
    }
    fclose(pArchivo);
}
