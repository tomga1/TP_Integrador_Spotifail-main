#pragma once
#include <string>
#include <iostream>
#include "Suscriptor.h"

class SuscriptoresArchivo {
public:

    SuscriptoresArchivo();
    SuscriptoresArchivo(const std::string &ruta);
    void setRuta(const std::string &ruta);
    std::string getRuta() const;
    bool escribir(Suscriptor &reg);
    bool sobrescribir(Suscriptor &reg, int indice);
    Suscriptor leer(int indice);
    int buscarPorId(int idSuscriptor);
    int buscarPorDni(int dni);
    int contarRegistros();
    void crearArchivoVacio();
    Suscriptor leerPorId(int idSuscriptor);

private:
    std::string _ruta;

};
