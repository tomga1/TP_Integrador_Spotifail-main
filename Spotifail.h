#pragma once
#include "Consola.h"
#include "SuscriptoresManager.h"
#include "AlbumsManager.h"
#include "CancionesManager.h"
#include "GenerosManager.h"
#include "InterpretesManager.h"
#include "AccesosManager.h"
#include "InformesManager.h"


class Spotifail {
public:
    void run();
    int login();
    void menuUtilidades();
    void about();

private:
    Consola _consola;
    SuscriptoresManager _suscriptoresManager;
    AlbumsManager _albumManager;
    CancionesManager _cancionManager;
    GenerosManager _generosManager;
    InterpretesManager _interpreteManager;
    AccesosManager _accesosManager;
    Suscriptor usuario;
    InformesManager _informes;
};
