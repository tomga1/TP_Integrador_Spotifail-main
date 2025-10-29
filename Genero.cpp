#include "Genero.h"

Genero::Genero()
{
    setIdGenero(1);
    setNombre("N/A");
    setInactivo(false);
}

Genero::Genero(int idGenero, std::string & nombre, bool inactivo)
{
    setIdGenero(idGenero);
    setNombre(nombre);
    setInactivo(inactivo);
}

int Genero::getIdGenero() { return _idGenero; }
void Genero::setIdGenero(int idGenero) { _idGenero = idGenero; }

const char* Genero::getNombre() { return _nombre; }
void Genero::setNombre(const std::string & nombre) { strcpy(_nombre, nombre.c_str()); }

bool Genero::getInactivo() { return _inactivo; }
void Genero::setInactivo(bool inactivo) { _inactivo = inactivo; }
