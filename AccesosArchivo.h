#pragma once
#include <string>
#include "Acceso.h"

class AccesosArchivo {
public:
    AccesosArchivo();
    AccesosArchivo(const std::string &path);
    void setPath(const std::string &path);
    std::string getPath() const;
    bool escribir(Acceso &reg);
    bool sobreEscribir(Acceso &reg, int indice);
    Acceso leer(int indice);
    int contarRegistros();
    void crearArchivoVacio();

private:
    std::string _path;

};
