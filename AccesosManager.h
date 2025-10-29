#pragma once
#include "AccesosArchivo.h"
#include "Consola.h"
#include <vector>
#include "SuscriptoresManager.h"

class AccesosManager {
public:
    AccesosManager();
    void mostrarMenu();
    void registrarAcceso(int idSuscriptor);
    void listarTodosLosAccesos(SuscriptoresManager& suscriptoresManager);
    void exportarBackup();
    void importarBackup();

private:
    AccesosArchivo _archivoAccesos;
    AccesosArchivo _backupAccesos;
    Consola _consola;
    SuscriptoresManager suscriptoresManager;

};
