#include "SuscriptoresArchivo.h"

SuscriptoresArchivo::SuscriptoresArchivo()
    : _ruta("registers/suscriptores.dat") {}

SuscriptoresArchivo::SuscriptoresArchivo(const std::string &ruta)
    : _ruta(ruta) {}

void SuscriptoresArchivo::setRuta(const std::string &ruta) {
    _ruta = ruta;
}

std::string SuscriptoresArchivo::getRuta() const {
    return _ruta;
}


bool SuscriptoresArchivo::escribir(Suscriptor &reg) {
    FILE *pArchivo = fopen(getRuta().c_str(), "ab");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo abrir el archivo para escritura.\n";
        return false;
    }

    bool ok = fwrite(&reg, sizeof(Suscriptor), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}


bool SuscriptoresArchivo::sobrescribir(Suscriptor &reg, int indice) {
    FILE *pArchivo = fopen(getRuta().c_str(), "rb+");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo abrir el archivo para sobrescritura.\n";
        return false;
    }

    fseek(pArchivo, sizeof(Suscriptor) * indice, SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Suscriptor), 1, pArchivo);
    fclose(pArchivo);
    return ok;
}


Suscriptor SuscriptoresArchivo::leer(int indice) {
    Suscriptor reg;
    FILE *pArchivo = fopen(getRuta().c_str(), "rb");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo abrir el archivo para lectura.\n";
        return reg;
    }

    fseek(pArchivo, sizeof(Suscriptor) * indice, SEEK_SET);
    fread(&reg, sizeof(Suscriptor), 1, pArchivo);
    fclose(pArchivo);
    return reg;
}


int SuscriptoresArchivo::buscarPorId(int idSuscriptor) {
    int i = 0;
    int total = contarRegistros();
    while (i < total) {
        Suscriptor reg = leer(i);
        if (reg.getIdSuscriptor() == idSuscriptor) return i;
        i++;
    }
    return -1;
}

Suscriptor SuscriptoresArchivo::leerPorId(int idSuscriptor) {
    int indice = buscarPorId(idSuscriptor);
    if (indice == -1) {
        Suscriptor vacio;
        return vacio;
    }
    return leer(indice);
}


int SuscriptoresArchivo::buscarPorDni(int dni) {
    int i = 0;
    int total = contarRegistros();
    while (i < total) {
        Suscriptor reg = leer(i);
        if (reg.getDni() == dni) return i;
        i++;
    }
    return -1;
}


int SuscriptoresArchivo::contarRegistros() {
    FILE *pArchivo = fopen(getRuta().c_str(), "rb");
    if (pArchivo == NULL) return 0;

    fseek(pArchivo, 0, SEEK_END);
    int bytes = ftell(pArchivo);
    fclose(pArchivo);

    return bytes / sizeof(Suscriptor);
}


void SuscriptoresArchivo::crearArchivoVacio() {
    FILE *pArchivo = fopen(getRuta().c_str(), "wb");
    if (pArchivo == NULL) {
        std::cerr << "Error: no se pudo crear el archivo.\n";
        return;
    }
    fclose(pArchivo);
}
