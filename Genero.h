#pragma once
#include <string>
#include <cstring>

class Genero
{
public:
    Genero();
    Genero(int idGenero, std::string & nombre, bool inactivo);
    int getIdGenero();
    void setIdGenero(int idGenero);
    const char* getNombre();
    void setNombre(const std::string & nombre);
    bool getInactivo();
    void setInactivo(bool inactivo);

private:
    int _idGenero;
    char _nombre[30];
    bool _inactivo;
};
