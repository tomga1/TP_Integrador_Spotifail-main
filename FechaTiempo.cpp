#include "FechaTiempo.h"

FechaTiempo::FechaTiempo()
{
    setFecha(Fecha());
    setTiempo(Tiempo());
}

FechaTiempo::FechaTiempo(Fecha fecha, Tiempo tiempo)
{
    setFecha(fecha);
    setTiempo(tiempo);
}

Fecha FechaTiempo::getFecha() { return _fecha; }
void FechaTiempo::setFecha(Fecha fecha) { _fecha = fecha; }

Tiempo FechaTiempo::getTiempo() { return _tiempo; }
void FechaTiempo::setTiempo(Tiempo tiempo) { _tiempo = tiempo; }

std::string FechaTiempo::toString() {
    return getFecha().toString() + " " + getTiempo().toString();
}
