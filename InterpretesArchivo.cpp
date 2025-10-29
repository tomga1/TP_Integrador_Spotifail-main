#include "InterpretesArchivo.h"
#include <iostream>
#include <cstdio>

InterpretesArchivo::InterpretesArchivo() : _ruta("registers/interpretes.dat") {}
InterpretesArchivo::InterpretesArchivo(const std::string &ruta) : _ruta(ruta) {}

void InterpretesArchivo::setRuta(const std::string &ruta) { _ruta = ruta; }
std::string InterpretesArchivo::getRuta() const { return _ruta; }

bool InterpretesArchivo::escribir(Interprete &reg) {
    FILE *pArchivo = fopen(getRuta().c_str(), "ab");
    if (!pArchivo) { std::cerr << "Error al abrir archivo para escritura.\n"; return false; }
    bool ok = fwrite(&reg, sizeof(Interprete), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

bool InterpretesArchivo::sobrescribir(Interprete &reg, int indice) {
    FILE *pArchivo = fopen(getRuta().c_str(), "rb+");
    if (!pArchivo) { std::cerr << "Error al abrir archivo para sobrescritura.\n"; return false; }
    fseek(pArchivo, sizeof(Interprete) * indice, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Interprete), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}

Interprete InterpretesArchivo::leer(int indice) {
    Interprete reg;
    FILE *pArchivo = fopen(getRuta().c_str(), "rb");
    if (!pArchivo) { std::cerr << "Error al abrir archivo para lectura.\n"; return reg; }
    fseek(pArchivo, sizeof(Interprete) * indice, SEEK_SET);
    fread(&reg, sizeof(Interprete), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}

Interprete InterpretesArchivo::leerPorId(int idInterprete) {
    int total = contarRegistros();
    for (int i = 0; i < total; i++) {
        Interprete reg = leer(i);
        if (reg.getIdInterprete() == idInterprete) return reg;
    }
    return Interprete();
}


int InterpretesArchivo::buscarPorId(int idInterprete) {
    int total = contarRegistros();
    for (int i = 0; i < total; i++) {
        Interprete reg = leer(i);
        if (reg.getIdInterprete() == idInterprete) return i;
    }
    return -1;
}

int InterpretesArchivo::buscarPorNombre(const std::string &nombre) {
    int total = contarRegistros();
    for (int i = 0; i < total; i++) {
        Interprete reg = leer(i);
        if (nombre == reg.getNombre()) return i;
    }
    return -1;
}

int InterpretesArchivo::contarRegistros() {
    FILE *pArchivo = fopen(getRuta().c_str(), "rb");
    if (!pArchivo) return 0;
    fseek(pArchivo, 0, SEEK_END);
    int bytes = ftell(pArchivo);
    fclose(pArchivo);
    return bytes / sizeof(Interprete);
}

void InterpretesArchivo::crearArchivoVacio() {
    FILE *pArchivo = fopen(getRuta().c_str(), "wb");
    if (!pArchivo) { std::cerr << "Error al crear archivo.\n"; return; }
    fclose(pArchivo);
}
