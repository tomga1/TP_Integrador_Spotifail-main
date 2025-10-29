#include "Interprete.h"

Interprete::Interprete()
{
    setIdInterprete(1);
    setNombre("N/A");
    setIdGenero(1);
    setActivo(true);
}

Interprete::Interprete(int idInterprete, std::string & nombre, int idGenero, bool activo){
    setIdInterprete(idInterprete);
    setNombre(nombre);
    setIdGenero(idGenero);
    setActivo(activo);
}
int Interprete::getIdInterprete(){ return _idInterprete; }

void Interprete::setIdInterprete(int idInterprete){
    _idInterprete = idInterprete;
}

const char* Interprete::getNombre() { return _nombre; }

void Interprete::setNombre(const std::string & nombre){
    strcpy(_nombre, nombre.c_str());
}

int Interprete::getIdGenero() { return _idGenero; }

void Interprete::setIdGenero(int idGenero){
    _idGenero = idGenero;
}

bool Interprete::getActivo() { return _activo; }

void Interprete::setActivo(bool activo){
    _activo = activo;
}
