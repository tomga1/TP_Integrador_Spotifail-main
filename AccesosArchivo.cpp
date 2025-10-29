#include "AccesosArchivo.h"
#include <iostream>
#include <cstdio>

AccesosArchivo::AccesosArchivo() : _path("registers/accesos.dat") {}
AccesosArchivo::AccesosArchivo(const std::string &path) : _path(path) {}

void AccesosArchivo::setPath(const std::string &path) { _path = path; }
std::string AccesosArchivo::getPath() const { return _path; }

bool AccesosArchivo::escribir(Acceso &reg) {
    FILE *p = fopen(_path.c_str(), "ab");
    if (!p) return false;
    bool ok = fwrite(&reg, sizeof(Acceso), 1, p);
    fclose(p);
    return ok;
}

bool AccesosArchivo::sobreEscribir(Acceso &reg, int indice) {
    FILE *p = fopen(_path.c_str(), "rb+");
    if (!p) return false;
    fseek(p, sizeof(Acceso) * indice, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Acceso), 1, p);
    fclose(p);
    return ok;
}

Acceso AccesosArchivo::leer(int indice) {
    Acceso reg;
    FILE *p = fopen(_path.c_str(), "rb");
    if (!p) return reg;
    fseek(p, sizeof(Acceso) * indice, SEEK_SET);
    fread(&reg, sizeof(Acceso), 1, p);
    fclose(p);
    return reg;
}

int AccesosArchivo::contarRegistros() {
    FILE *p = fopen(_path.c_str(), "rb");
    if (!p) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Acceso);
}

void AccesosArchivo::crearArchivoVacio() {
    FILE *p = fopen(_path.c_str(), "wb");
    if (p) fclose(p);
}


