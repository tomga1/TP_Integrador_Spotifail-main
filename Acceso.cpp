#include "Acceso.h"

Acceso::Acceso()
{
    setIdAcceso(1);
    setIdSuscriptor(1);
    setIdCancion(1);
    setFechaHora(FechaTiempo());
    setInactivo(false);
}

Acceso::Acceso(int idAcceso, int idSuscriptor, int idCancion, FechaTiempo fechaHora, bool inactivo)
{
    setIdAcceso(idAcceso);
    setIdSuscriptor(idSuscriptor);
    setIdCancion(idCancion);
    setFechaHora(fechaHora);
    setInactivo(inactivo);
}

int Acceso::getIdAcceso() { return _idAcceso; }
void Acceso::setIdAcceso(int idAcceso) { _idAcceso = idAcceso; }

int Acceso::getIdSuscriptor() { return _idSuscriptor; }
void Acceso::setIdSuscriptor(int idSuscriptor) { _idSuscriptor = idSuscriptor; }

int Acceso::getIdCancion() { return _idCancion; }
void Acceso::setIdCancion(int idCancion) { _idCancion = idCancion; }

FechaTiempo Acceso::getFechaHora() { return _fechaHora; }
void Acceso::setFechaHora(FechaTiempo fechaHora) { _fechaHora = fechaHora; }

bool Acceso::getInactivo() { return _inactivo; }
void Acceso::setInactivo(bool inactivo) { _inactivo = inactivo; }
