#pragma once
#include "Consola.h"
#include "Suscriptor.h"
#include "Acceso.h"
#include "AccesosArchivo.h"
#include "SuscriptoresArchivo.h"



class InformesManager {
public:
    InformesManager();
    void mostrarMenu();
    void informeCantidadAccesosPorSuscriptor();
    void informeUsuariosInactivos();


private:
    Consola _consola;
    AccesosArchivo _archivoAcceso;
    SuscriptoresArchivo _archivoSuscriptores;
    void mostrarEncabezado(const char* titulo);
};
