#pragma once
#include "FechaTiempo.h"

class Acceso
{
public:
    Acceso();
    Acceso(int idAcceso, int idSuscriptor, int idCancion, FechaTiempo fechaHora, bool inactivo);
    int getIdAcceso();
    void setIdAcceso(int idAcceso);
    int getIdSuscriptor();
    void setIdSuscriptor(int idSuscriptor);
    int getIdCancion();
    void setIdCancion(int idCancion);
    FechaTiempo getFechaHora();
    void setFechaHora(FechaTiempo fechaHora);
    bool getInactivo();
    void setInactivo(bool inactivo);

private:
    int _idAcceso;
    int _idSuscriptor;
    int _idCancion;
    FechaTiempo _fechaHora;
    bool _inactivo;
};
