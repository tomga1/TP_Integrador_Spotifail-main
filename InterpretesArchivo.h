#pragma once
#include "Interprete.h"
#include <string>

class InterpretesArchivo {
public:
    InterpretesArchivo();
    InterpretesArchivo(const std::string &ruta);
    void setRuta(const std::string &ruta);
    std::string getRuta() const;
    bool escribir(Interprete &reg);
    bool sobrescribir(Interprete &reg, int indice);
    Interprete leer(int indice);
    int buscarPorId(int idInterprete);
    int buscarPorNombre(const std::string &nombre);
    int contarRegistros();
    void crearArchivoVacio();
    Interprete leerPorId(int idInterprete);

private:
    std::string _ruta;
};
