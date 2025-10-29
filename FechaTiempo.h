#pragma once
#include "Fecha.h"
#include "Tiempo.h"

class FechaTiempo
{
public:
    FechaTiempo();
    FechaTiempo(Fecha fecha, Tiempo tiempo);
    Fecha getFecha();
    void setFecha(Fecha fecha);
    Tiempo getTiempo();
    void setTiempo(Tiempo tiempo);
    std::string toString();

private:
    Fecha _fecha;
    Tiempo _tiempo;
};
